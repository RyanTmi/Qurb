/// \file MetalRenderBackend.hpp

#pragma once

#include <RHI/RenderBackend.hpp>

namespace qurb::rhi::metal
{
    /// \brief The `RenderBackend` class.
    class RenderBackend final : public rhi::RenderBackend
    {
    public:
        using base = rhi::RenderBackend;

    public:
        ~RenderBackend() override = default;

    public:
        auto type() const -> RenderBackendType override;
        auto createDevice() const -> rhi::Device* override;
    };

    inline auto RenderBackend::type() const -> RenderBackendType
    {
        return RenderBackendType::Metal;
    }
}
