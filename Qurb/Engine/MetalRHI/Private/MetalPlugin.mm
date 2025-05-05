#include "MetalPlugin.hpp"

using qurb::DynamicLibrary;
using qurb::MetalRHIPlugin;
using qurb::Plugin;

extern "C"
{
    QURB_METAL_RHI_API auto createPlugin(DynamicLibrary* library) -> Plugin*
    {
        return new MetalRHIPlugin(std::move(*library));
    }
}
