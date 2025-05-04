/// \file Exceptions.hpp

#pragma once

#include "CoreDefines.hpp"

#include <source_location>
#include <stdexcept>
#include <string>
#include <string_view>

namespace qurb
{
    /// \brief Base class for all exceptions in the Qurb engine.
    class QURB_API Exception : public std::runtime_error
    {
    public:
        explicit Exception(std::string_view error);
    };

    inline Exception::Exception(std::string_view error)
        : std::runtime_error(error.data())
    {}

    /// \brief Exception thrown when a function is not implemented.
    class QURB_API NotImplementedError final : public std::runtime_error
    {
    public:
        explicit NotImplementedError(const std::source_location& location = std::source_location::current());
    };

    inline NotImplementedError::NotImplementedError(const std::source_location& location)
        : std::runtime_error(std::string(location.function_name()) + ": is not implemented.")
    {}
}

