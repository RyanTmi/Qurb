/// \file Platform.hpp

#pragma once

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
