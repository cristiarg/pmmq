#pragma once

#include <string>
#include <memory>

namespace pmmq {

    struct Message {
    public:
        Message(wchar_t _type, std::wstring _contents)
            : type{ _type }
            , contents{ _contents }
        {
        }

        const wchar_t type;
        const std::wstring contents;
    };

    using XMessage = std::shared_ptr<Message>;

}
