#include "Platform/DynamicLibrary.hpp"

#include "Debug/Ensure.hpp"
#include "Log/Log.hpp"

#include <algorithm>
#include <dlfcn.h>

namespace qurb
{
    DynamicLibrary::DynamicLibrary()
        : _nativeHandle(nullptr)
    {}

    DynamicLibrary::DynamicLibrary(std::string_view name)
        : DynamicLibrary()
    {
        load(name);
    }

    DynamicLibrary::~DynamicLibrary()
    {
        unload();
    }

    DynamicLibrary::DynamicLibrary(DynamicLibrary&& other) noexcept
        : _name(std::move(other._name))
        , _nativeHandle(other._nativeHandle)
        , _functions(std::move(other._functions))
    {
        other._nativeHandle = nullptr;
    }

    auto DynamicLibrary::operator=(DynamicLibrary&& other) noexcept -> DynamicLibrary&
    {
        if (this != &other)
        {
            _name         = std::move(other._name);
            _nativeHandle = other._nativeHandle;
            _functions    = std::move(other._functions);

            other._nativeHandle = nullptr;
        }

        return *this;
    }

    auto DynamicLibrary::load(std::string_view name) -> void
    {
        _name = name;

        const auto fullName = "lib" + _name + ".dylib";
        _nativeHandle       = dlopen(fullName.c_str(), RTLD_NOW);
        ensure(_nativeHandle != nullptr, "Failed to load dynamic library: {}: {}.", _name, dlerror());
    }

    auto DynamicLibrary::unload() -> void
    {
        _functions.clear();
        _name.clear();
        if (_nativeHandle == nullptr)
        {
            return;
        }

        if (dlclose(_nativeHandle) == -1)
        {
            Log::error("Failed to close dynamic library: {}: {}.", _name, dlerror());
        }
    }

    template <>
    auto DynamicLibrary::loadFunction<void*>(std::string_view name) -> void*
    {
        ensure(isOpen(), "Dynamic library is not open: {}: cannot load function.", _name);

        // Check if the function is already loaded
        auto it = std::ranges::find_if(_functions, [&](const auto& fn) { return fn.name == name; });
        if (it != _functions.end())
        {
            Log::warn("Function '{}' already loaded from dynamic library: {}.", name, _name);
            return it->fn;
        }

        auto fn = dlsym(_nativeHandle, name.data());
        ensure(fn != nullptr, "Failed to load function: {}: {}.", name, dlerror());

        _functions.emplaceBack(std::string(name), fn);
        Log::debug("Loaded function: {} from dynamic library: {}.", name, _name);
        return fn;
    }
}
