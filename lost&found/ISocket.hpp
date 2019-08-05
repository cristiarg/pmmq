#pragma once

#include <memory>
#include <Broker.hpp>
#include "Message.hpp"

class ISocket {
public:
    //ISocket(const XBroker& broker);
    virtual ~ISocket() = 0 {};

    virtual XMessage recv() = 0;

    virtual void send(XMessage) = 0;
};

using XISocket = std::shared_ptr<ISocket>;
