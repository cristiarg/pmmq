#include <memory>

class IConsumer {
public:
    virtual ~IConsumer() = 0 {};
};

using XIConsumer = std::shared_ptr<IConsumer>;