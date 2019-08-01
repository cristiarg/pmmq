#pragma once

#include <memory>

class IProducer {
public:
    virtual ~IProducer() = 0 {};

    //virtual int get_id() = 0;
};

using XIProducer = std::shared_ptr<IProducer>;