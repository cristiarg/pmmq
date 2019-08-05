#include "Broker.hpp"

namespace pmmq {

    Broker::Broker()
    {
    }

    int Broker::subscribe(const XIConsumer&)//_producer)
    {
        // TODO: async subscribe
        return -1;
    }

    int Broker::unsubscribe(const XIConsumer&)//_producer)
    {
        // TODO: async unsubscribe
        return -1;
    }

    // TODO: async subscribe routing using the mutex
    // TODO: async unsubscribe routing using the mutex

    // TODO: launch thread to monitor and process message queues

}
