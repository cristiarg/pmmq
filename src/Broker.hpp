#pragma once

#include <vector>
#include <map>
#include <memory>
#include <set>
#include <mutex>

#include "Message.hpp"
#include "IConsumer.hpp"

namespace pmmq {

    class Broker {
    public:
        Broker();

    public:
        int subscribe(const XIConsumer& _consumer);
        int unsubscribe(const XIConsumer& _consumer);

        int dispatch(XMessage& _message) const;

    private:
        using ConsumerVector = std::vector<XIConsumer>;
        using MessageTypeToConsumerVectorMap = std::map<wchar_t, ConsumerVector>;
        using ConsumerSet = std::set<XIConsumer>;

        MessageTypeToConsumerVectorMap mapping;

        ConsumerSet bookkeeping;

        mutable std::mutex dispatch_mutex;
    };

    using XBroker = std::shared_ptr<Broker>;
}