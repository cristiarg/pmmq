#pragma once

#include <memory>
#include "Message.hpp"

namespace pmmq {

    class IConsumer {
    public:
        IConsumer(wchar_t _message_type);

        IConsumer(const IConsumer&) = delete;
        IConsumer(IConsumer&&) = delete;
        IConsumer& operator=(const IConsumer&) = delete;
        IConsumer& operator=(IConsumer&&) = delete;

        virtual ~IConsumer() = 0 {};

        wchar_t getSubscribedMessageType() const;

        virtual void consume(const XMessage& _message) const = 0;

    private:
        const wchar_t message_type;
    };

    using XIConsumer = std::shared_ptr<IConsumer>;

}