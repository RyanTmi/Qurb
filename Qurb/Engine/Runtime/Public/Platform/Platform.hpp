/// \file Platform.hpp

#pragma once

#include "Platform/Window.hpp"

namespace qurb
{
    /// \brief The `Platform` class
    class Platform final
    {
    public:
        struct NativeHandle;

    public:
        Platform();
        ~Platform();

    public:
        auto pollEvents() -> void;

    private:
        NativeHandle* _nativeHandle;
    };
}
