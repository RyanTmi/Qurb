/// \file DynamicLibrary.hpp

#pragma once

#include "Containers/Vector.hpp"
#include "CoreDefines.hpp"

#include <string>
#include <string_view>

namespace qurb
{
    /// \brief The `DynamicLibrary` class.
    class QURB_API DynamicLibrary
    {
    public:
        DynamicLibrary();
        explicit DynamicLibrary(std::string_view name);

        ~DynamicLibrary();

        DynamicLibrary(const DynamicLibrary&)                    = delete;
        auto operator=(const DynamicLibrary&) -> DynamicLibrary& = delete;

        DynamicLibrary(DynamicLibrary&& other) noexcept;
        auto operator=(DynamicLibrary&& other) noexcept -> DynamicLibrary&;

    public:
        [[nodiscard]] auto isOpen() const -> bool;
        [[nodiscard]] auto name() const -> std::string_view;

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

    inline auto DynamicLibrary::name() const -> std::string_view
    {
        return _name;
    }

    template <typename T>
    auto DynamicLibrary::loadFunction(std::string_view name) -> T
    {
        return reinterpret_cast<T>(loadFunction<void*>(name));
    }
}
