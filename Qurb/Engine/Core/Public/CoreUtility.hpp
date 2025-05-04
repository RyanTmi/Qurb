/// \file CoreUtility.hpp

#pragma once

#include <functional>

namespace qurb
{
    template <typename T, typename... Args>
    auto hashCombine(std::size_t& hash, const T& value, const Args&... args) -> void
    {
        hash ^= std::hash<T>()(value) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
        (hashCombine(hash, args), ...);
    }
}
