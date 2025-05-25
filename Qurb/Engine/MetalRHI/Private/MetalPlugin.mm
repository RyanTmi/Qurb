#include "MetalPlugin.hpp"

using namespace qurb;

extern "C"
{
    QURB_METAL_RHI_API auto createPlugin(DynamicLibrary* library) -> Plugin*
    {
        return new rhi::metal::Plugin(std::move(*library));
    }
}
