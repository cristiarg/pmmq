#define CATCH_CONFIG_MAIN

#include <iostream>
#include <strstream>

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

    void produce()
    {
        for (int i = 0; i < message_count; i++) {
            std::wstringstream ss;
            ss << L"Message " << (i + 1) << L" of type " << message_type << L" from producer " << id;
            auto m = std::make_shared<pmmq::Message>(message_type, ss.str());
            broker->dispatch(m);
        }
    }

private:
    pmmq::XBroker broker;
    const wchar_t message_type;
    const int id;
    const int message_count;
};
using XProducer1 = std::shared_ptr<Producer1>;


class Consumer1 : public pmmq::IConsumer {
public:
    Consumer1(const wchar_t _message_type)
        : pmmq::IConsumer(_message_type)
        , consumed_count{0}
    {
    }

    Consumer1::~Consumer1() override
    {
    }

    void Consumer1::consume(pmmq::XMessage& _message) const override
    {
        std::wcout << _message->contents << std::endl;
        REQUIRE(_message->contents.size() > 0);
        ++consumed_count;
    }

    int get_consumed_count() const
    {
        return consumed_count;
    }

private:
    mutable int consumed_count;
};

static const int PROD_COUNT{ 3 };
static const int CONS_COUNT{ 275 };
static const int MESS_COUNT{ 23 };


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
        prod->produce();
    }

    for (auto cons : cons_vec) {
        const Consumer1* const cons1 = dynamic_cast<Consumer1*>(cons.get());
        REQUIRE(MESS_COUNT * PROD_COUNT == cons1->get_consumed_count());
    }
}

