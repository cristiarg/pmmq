#pragma once

#include <memory>
#include <cassert>

#include "IProducer.hpp"

namespace pmmq {

    IProducer::IProducer(XBroker& _broker)
            : broker{ _broker }
    {
        assert(_broker != nullptr);
    }

    int IProducer::dispatch(XMessage& _message)
    {
        if (_message != nullptr) {
            broker->dispatch(_message);
            return 0;
        }
        else {
            return -1;
        }
    }

}