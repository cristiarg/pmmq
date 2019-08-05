#pragma once

#include <string>
#include <memory>

namespace pmmq {

    struct Message {
    public:
        const wchar_t type;
        const std::wstring contents;
    };

    using XMessage = std::shared_ptr<Message>;

}
