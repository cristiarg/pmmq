#pragma once

#include <memory>

#include "Message.hpp"
#include "Broker.hpp"

namespace pmmq {

    class IProducer {
    public:
        IProducer(XBroker& _broker);

        IProducer(const XBroker&  ) = delete;
        IProducer(      XBroker&& ) = delete;
        IProducer& operator=(const XBroker&  ) = delete;
        IProducer& operator=(      XBroker&& ) = delete;

        virtual ~IProducer() = 0 {};

        int dispatch(XMessage& _message) /*const*/;

    private:
        /*const*/ XBroker broker;
    };

    using XIProducer = std::shared_ptr<IProducer>;

}