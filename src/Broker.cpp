#include "Broker.hpp"

namespace pmmq {

    Broker::Broker()
    {
    }

    int Broker::subscribe(const XIConsumer& _consumer)
    {
        if (_consumer != nullptr && bookkeeping.find(_consumer) == bookkeeping.end()) {
            bookkeeping.insert(_consumer);
            mapping[_consumer->get_message_type()].push_back(_consumer);
            return 0;
        }
        else {
            return -1;
        }
    }

    int Broker::unsubscribe(const XIConsumer& _consumer)
    {
        if (_consumer != nullptr) {
            const auto it = bookkeeping.find(_consumer);
            if (it != bookkeeping.end()) {
                bookkeeping.erase(it);
                const auto message_type = _consumer->get_message_type();
                auto message_type_mapping = mapping[message_type];
                for (auto it = message_type_mapping.begin(); it != message_type_mapping.end(); it++) {
                    if (_consumer == *it) {
                        message_type_mapping.erase(it);
                        break;
                    }
                }
                return 0;
            }
            else {
                return -1;
            }
        }
        else {
            return -1;
        }
    }

    int Broker::dispatch(XMessage& _message) const
    {
        const auto consumer_vec_it = mapping.find(_message->type);
        if (consumer_vec_it != mapping.end()) {
            for (auto consume_it : consumer_vec_it->second) {
                std::lock_guard<std::mutex> lkg(dispatch_mutex);

                (*consume_it).consume(_message);

                std::this_thread::yield();
            }
            return 0;
        }
        else {
            return -1;
        }
    }

}
