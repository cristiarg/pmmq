#pragma once

#include <string>

struct Message {
public:
    const wchar_t type;
    const std::wstring contents;
};