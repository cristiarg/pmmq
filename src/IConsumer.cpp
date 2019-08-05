#include "IConsumer.hpp"

namespace pmmq {

    IConsumer::IConsumer(wchar_t _message_type)
        : message_type{_message_type}
    {
    }

    wchar_t IConsumer::getSubscribedMessageType() const
    {
        return message_type;
    }

}
