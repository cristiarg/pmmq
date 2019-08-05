#pragma once

#include <vector>
#include <map>
#include <memory>
#include <mutex>

#include "Message.hpp"
#include "IConsumer.hpp"

namespace pmmq {

    // TODO: singleton?
    class Broker {
    public:
        Broker();

    public:
        int subscribe(const XIConsumer& _consumer);
        int unsubscribe(const XIConsumer& _consumer);

    private:
        using ConsumerVector = std::vector<XIConsumer>;
        using MessageTypeToConsumerVectorMap = std::map<wchar_t, ConsumerVector>;

        //std::mutex concurrent_access_to_message_consumers_mapping;

        MessageTypeToConsumerVectorMap message_type_to_consumers_mapping;
    };

    using XBroker = std::shared_ptr<Broker>;

}