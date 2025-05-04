/// \file DynamicLibrary.hpp

#pragma once

#include "Containers/Vector.hpp"
#include "CoreDefines.hpp"

#include <string>
#include <string_view>
#include <vector>

namespace qurb
{
    /// \brief A class reprensenting a dynamic library.
    class QURB_API DynamicLibrary
    {
    public:
        DynamicLibrary();
        explicit DynamicLibrary(std::string_view name);

        ~DynamicLibrary();

        DynamicLibrary(const DynamicLibrary&)                    = delete;
        auto operator=(const DynamicLibrary&) -> DynamicLibrary& = delete;

    public:
        [[nodiscard]] auto isOpen() const -> bool;

        auto load(std::string_view name) -> void;
        auto unload() -> void;

        template <typename T = void*>
        auto loadFunction(std::string_view name) -> T;

    private:
        struct Function
        {
            std::string name;
            void*       fn;
        };

    private:
        std::string      _name;
        void*            _nativeHandle;
        Vector<Function> _functions;
    };

    inline auto DynamicLibrary::isOpen() const -> bool
    {
        return _nativeHandle != nullptr;
    }

    template <typename T>
    auto DynamicLibrary::loadFunction(std::string_view name) -> T
    {
        return reinterpret_cast<T>(loadFunction<void*>(name));
    }
}
