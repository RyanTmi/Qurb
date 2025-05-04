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

    auto DynamicLibrary::load(std::string_view name) -> void
    {
        _name = name;

        const auto fullName = _name + ".dylib";
        _nativeHandle       = dlopen(fullName.c_str(), RTLD_NOW);
        ensure(_nativeHandle != nullptr, "Failed to load dynamic library: {}: {}.", _name, dlerror());

        Log::debug("Loaded dynamic library: {}", _name);
    }

    auto DynamicLibrary::unload() -> void
    {
        if (!_nativeHandle)
        {
            Log::warn("No dynamic library to unload.");
            return;
        }

        if (dlclose(_nativeHandle) == -1)
        {
            Log::error("Failed to close dynamic library: {}: ", _name, dlerror());
        }
    }

    template <>
    auto DynamicLibrary::loadFunction<void*>(std::string_view name) -> void*
    {
        ensure(isOpen(), "Dynamic library is not open: {}: ", _name);

        // Check if the function is already loaded
        auto it = std::ranges::find_if(_functions, [&](const Function& fn) { return fn.name == name; });
        if (it != _functions.end())
        {
            return it->fn;
        }

        auto fn = dlsym(_nativeHandle, name.data());
        ensure(fn != nullptr, "Failed to load function: {}: ", name, dlerror());

        _functions.emplaceBack(std::string(name), fn);
        Log::debug("Loaded function: {} from dynamic library: {}", name, _name);
        return fn;
    }
}
