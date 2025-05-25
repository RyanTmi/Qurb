/// \file Plugin.hpp

#pragma once

#include "CoreDefines.hpp"
#include "Platform/DynamicLibrary.hpp"

#include <string>
#include <string_view>

namespace qurb
{
    /// \brief The `Plugin` class.
    class QURB_API Plugin
    {
    public:
        explicit Plugin(DynamicLibrary&& library);
        virtual ~Plugin() = default;

    public:
        [[nodiscard]] auto libraryName() const -> std::string_view;

    public:
        virtual auto name() const -> std::string_view        = 0;
        virtual auto description() const -> std::string_view = 0;
        virtual auto version() const -> std::string_view     = 0;

        virtual auto initialize() -> void {}

    private:
        DynamicLibrary _library;
    };

    inline Plugin::Plugin(DynamicLibrary&& library)
        : _library(std::move(library))
    {}

    inline auto Plugin::libraryName() const -> std::string_view
    {
        return _library.name();
    }
}
