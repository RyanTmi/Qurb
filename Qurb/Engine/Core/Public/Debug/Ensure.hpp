/// \file Ensure.hpp

#pragma once

#include "Debug/Exceptions.hpp"

#include <format>

namespace qurb
{
    // TODO: Use std::source_location to provide more information.
    template <typename... Args>
    QURB_API auto ensure(bool condition, std::format_string<Args...> format, Args&&... args) -> void
    {
#ifndef NDEBUG
        if (!condition)
        {
            const auto errorMessage = std::format(format, std::forward<Args>(args)...);
            throw Exception(errorMessage);
        }
#endif
    }
}
