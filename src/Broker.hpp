#pragma once

#include <vector>
#include <map>
#include <memory>
#include <set>
#include <mutex>
#include <queue>
#include <atomic>

#include "Message.hpp"
#include "IConsumer.hpp"

namespace pmmq {

    class Broker {

    private: // types
        enum class SubscribeType {
            SUBSCR,
            UNSUBS,
        };

        struct SubscribeRequest {
            SubscribeType type;
            const XIConsumer consumer;
        };
        
    public: // ctors
        Broker();
        ~Broker();

        Broker(const Broker&) = delete;
        Broker(      Broker&&) = delete;
        Broker& operator=(const Broker&) = delete;
        Broker& operator=(      Broker&&) = delete;

    public: // API methods
        int subscribe(const XIConsumer& _consumer);
        int unsubscribe(const XIConsumer& _consumer);

        int dispatch(XMessage& _message);

    private: // methods
        void processing_loop();

    private: // members
        // subscribe/unsubscribe queue
        //
        //  - a queue of messages to either subscribe or unsubscribe consumers
        //  - use the mutex to guard adding requests to subscribe/unsubscribe
        //  - once at least a request is found here, the background processing thread
        //      uses the mutex to 'atomically' clear out the 
        using SubscribeRequestQueue = std::queue<SubscribeRequest>;
        SubscribeRequestQueue subscribe_unsubscribe_queue;
        std::mutex subscribe_unsubscribe_queue_mutex;

        // message queue
        //
        //  - a queue of messages
        //  - use a mutex to guard access
        //  - a background processing thread takes all messages from here in an
        //      'atomic' oepration and processes them
        using MessageQueue = std::queue<XMessage>;
        MessageQueue message_queue;
        std::mutex message_queue_mutex;

        // processing queue
        //
        //  - TODO: later, async tasks to dispatch messages

        // consumers bookkeeping
        //
        //  - access to these resources should be done only from a background working thread
        //  - so, there should not be any upfront locking - in a first phase
        //  - in a second phase, we might split message dispatching in a more async way and, therefore
        //      require that we guard access here as well
        using ConsumerVector = std::vector<XIConsumer>;
        using MessageTypeToConsumerVectorMap = std::map<wchar_t, ConsumerVector>;
        using ConsumerSet = std::set<XIConsumer>;

        MessageTypeToConsumerVectorMap mapping;
        ConsumerSet bookkeeping;

        // worker thread
        //
        std::thread worker_thread;
        std::atomic_bool stop_worker_thread_requested;

        // TODO: ideeas:
        //  - introduce also a condition variable such that to avoid polling
        //      from the processing thread for new messages/subscribe events
    };

    using XBroker = std::shared_ptr<Broker>;
}