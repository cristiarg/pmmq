#include "IConsumer.hpp"

namespace pmmq {

    IConsumer::IConsumer(wchar_t _message_type)
        : message_type{_message_type}
    {
    }

    wchar_t IConsumer::get_message_type() const
    {
        return message_type;
    }

}
