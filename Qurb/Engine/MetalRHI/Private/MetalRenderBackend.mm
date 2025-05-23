#include "MetalRenderBackend.hpp"

#include "MetalDevice.hpp"

namespace qurb::rhi::metal
{
    auto RenderBackend::createDevice() const -> rhi::Device*
    {
        return new Device();
    }
}
