#include "Broker.hpp"

#include <chrono>

namespace pmmq {

    Broker::Broker()
        : worker_thread{&Broker::processing_loop, this}
        , stop_worker_thread_requested(false)
    {
    }

    Broker::~Broker()
    {
        if (worker_thread.joinable()) {
            stop_worker_thread_requested = true;
            worker_thread.join();
        }
    }


    int Broker::subscribe(const XIConsumer& _consumer)
    {
        std::lock_guard<std::mutex> lock{subscribe_unsubscribe_queue_mutex};

        subscribe_unsubscribe_queue.push({SubscribeType::SUBSCR, _consumer});
        //if (_consumer != nullptr && bookkeeping.find(_consumer) == bookkeeping.end()) {
        //    bookkeeping.insert(_consumer);
        //    mapping[_consumer->get_message_type()].push_back(_consumer);
        //    return 0;
        //}
        //else {
        //    return -1;
        //}
        return 0;
    }

    int Broker::unsubscribe(const XIConsumer& _consumer)
    {
        std::lock_guard<std::mutex> lock{subscribe_unsubscribe_queue_mutex};

        subscribe_unsubscribe_queue.push({SubscribeType::UNSUBS, _consumer});

        //if (_consumer != nullptr) {
        //    const auto it = bookkeeping.find(_consumer);
        //    if (it != bookkeeping.end()) {
        //        bookkeeping.erase(it);
        //        const auto message_type = _consumer->get_message_type();
        //        auto message_type_mapping = mapping[message_type];
        //        for (auto it = message_type_mapping.begin(); it != message_type_mapping.end(); it++) {
        //            if (_consumer == *it) {
        //                message_type_mapping.erase(it);
        //                break;
        //            }
        //        }
        //        return 0;
        //    }
        //    else {
        //        return -1;
        //    }
        //}
        //else {
        //    return -1;
        //}
        return 0;
    }


    int Broker::dispatch(XMessage& _message)
    {
        const auto consumer_vec_it = mapping.find(_message->type);
        if (consumer_vec_it != mapping.end()) {
            for (auto consume_it : consumer_vec_it->second) {
                (*consume_it).consume(_message);
            }
            return 0;
        }
        else {
            return -1;
        }
    }

    void Broker::processing_loop()
    {
        while (true) {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));

            if (stop_worker_thread_requested.load()) {
                stop_worker_thread_requested = false;
                break;
            }
        }
    }

}
