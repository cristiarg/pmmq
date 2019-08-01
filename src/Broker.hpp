#pragma once

#include "Message.hpp"
#include "IProducer.hpp"
#include "IConsumer.hpp"

class Broker {
public:
    Broker();

public:
    int subscribe(const XIProducer& _producer);
    int subscribe(const XIConsumer& _producer);

    int unsubscribe(const XIProducer& _producer);
    int unsubscribe(const XIConsumer& _producer);
};