/// \file RenderBackend.hpp

#pragma once

#include "RHI/Device.hpp"

namespace qurb::rhi
{
    /// \brief The `RenderBackendType` enum.
    enum class RenderBackendType
    {
        None,
        Metal,
        Vulkan,
        D3D12,
    };

    /// \brief The `RenderBackend` class.
    class RenderBackend
    {
    public:
        virtual ~RenderBackend() = default;

    public:
        virtual auto type() const -> RenderBackendType = 0;
        virtual auto createDevice() const -> Device*   = 0;
    };
}
