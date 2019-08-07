#define CATCH_CONFIG_MAIN

#include <iostream>
#include <strstream>
#include <thread>
#include <atomic>
#include <queue>
#include <condition_variable>

#include "catch.hpp"

#include "Message.hpp"
#include "Broker.hpp"
#include "IConsumer.hpp"

class Producer1 {
public:
    Producer1(pmmq::XBroker& _broker, wchar_t _message_type, int _id, int _message_count)
        : broker{_broker}
        , message_type{_message_type}
        , id{_id}
        , message_count{_message_count}
    {
    }

    void start_produce()
    {
        internal_join();

        produce_thread = std::thread(&Producer1::internal_produce, this);
    }

    void end_produce()
    {
        internal_join();
    }

private:
    void internal_produce()
    {
        for (int i = 0; i < message_count; i++) {
            std::wstringstream ss;
            ss << L"Message " << (i + 1) << L" of type '" << message_type << L"' from producer " << id;
            auto m = std::make_shared<pmmq::Message>(message_type, ss.str());
            broker->dispatch(m);
        }
    }

    void internal_join() {
        if (produce_thread.joinable()) {
            produce_thread.join();
        }
    }

private:
    pmmq::XBroker broker;
    const wchar_t message_type;
    const int id;
    const int message_count;

    std::thread produce_thread;
};
using XProducer1 = std::shared_ptr<Producer1>;


class Consumer1 : public pmmq::IConsumer {
public:
    Consumer1(const wchar_t _message_type)
        : pmmq::IConsumer(_message_type)
        , consumed_count{0}
        , stop{false}
        , messages_might_be_available{false}
    {
        consume_thread = std::thread( &Consumer1::internal_consume, this );
    }

    ~Consumer1() override
    {
        end_consume();
    }

    void consume(pmmq::XMessage& _message) const override
    {
        {
            std::lock_guard<std::mutex> lck(message_mutex);
            message_queue.push(_message);
            messages_might_be_available = true;
        }
        message_cv.notify_one();
    }

    void end_consume()
    {
        stop.store(true);
        if (consume_thread.joinable()) {
            messages_might_be_available = true;
            message_cv.notify_one();
            consume_thread.join();
        }
    }

    int get_consumed_count() const
    {
        return consumed_count;
    }

private:
    void internal_consume()
    {
        while (!stop.load()) {
            std::queue<pmmq::XMessage> locally_copied_message_queue;

            // check for new messages
            {
                std::unique_lock<std::mutex> ulck{message_mutex};
                message_cv.wait(ulck, [this]{
                        return messages_might_be_available;
                    });
                assert(locally_copied_message_queue.empty());
                std::swap(locally_copied_message_queue, message_queue);

                messages_might_be_available = false;
            }

            locked_consume(locally_copied_message_queue);
        }

        //{
        //    std::queue<pmmq::XMessage> locally_copied_message_queue;

        //    // check for the last messages
        //    {
        //        std::unique_lock<std::mutex> ulck{message_mutex};

        //        // not needed to wait on the variable since teh variable might only be triggered
        //        // once while we're still in the main loop
        //        //message_cv.wait(ulck, [this]{
        //        //        return messages_might_be_available;
        //        //    });
        //        assert(locally_copied_message_queue.empty());
        //        std::swap(locally_copied_message_queue, message_queue);

        //        //messages_might_be_available= false;
        //    }

        //    locked_consume(locally_copied_message_queue);
        //}
    }

    void locked_consume(std::queue<pmmq::XMessage>& _message_queue)
    {
        while (_message_queue.empty() == false) {
            auto message = _message_queue.front();
            _message_queue.pop();

            //std::wcout << _message->contents << std::endl;
            //std::this_thread::sleep_for(std::chrono::milliseconds(20));
            ++consumed_count;
        }
    }

private:
    int consumed_count;

    std::thread consume_thread;

    mutable std::queue<pmmq::XMessage> message_queue;
    mutable std::mutex message_mutex;

    mutable std::condition_variable message_cv;
    mutable bool messages_might_be_available;

    std::atomic_bool stop;
};

static const int PROD_COUNT{ 30 };
static const int CONS_COUNT{ 50 };
static const int MESS_COUNT{ 120 };


TEST_CASE("Broker 1")
{
    int res{0};

    auto brok = std::make_shared<pmmq::Broker>();
    REQUIRE(brok != nullptr);

    std::vector<XProducer1> prod_vec;
    for (int i = 0; i < PROD_COUNT; i++) {
        prod_vec.push_back(std::make_shared<Producer1>(brok, L'a', (i + 1), MESS_COUNT));
    }

    std::vector<pmmq::XIConsumer> cons_vec;
    for (int i = 0; i < CONS_COUNT; i++) {
        auto cons = std::make_shared<Consumer1>(L'a');

        brok->subscribe(cons);

        cons_vec.push_back(cons);
    }

    for (auto prod : prod_vec) {
        prod->start_produce();
    }

    for (auto prod : prod_vec) {
        prod->end_produce();
    }

    for (auto cons : cons_vec) {
        Consumer1* const cons1 = dynamic_cast<Consumer1*>(cons.get());
        cons1->end_consume();
    }

    for (auto cons : cons_vec) {
        const Consumer1* const cons1 = dynamic_cast<Consumer1*>(cons.get());
        REQUIRE(MESS_COUNT * PROD_COUNT == cons1->get_consumed_count());
    }
}

