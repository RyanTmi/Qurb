/// \file MetalRenderBackend.hpp

#pragma once

#include <RHI/RenderBackend.hpp>

namespace qurb
{
    /// \brief The `MetalRenderBackend` class.
    class MetalRenderBackend final : public RenderBackend
    {
    public:
        ~MetalRenderBackend() override = default;

    public:
        auto type() const -> RenderBackendType override;
    };

    inline auto MetalRenderBackend::type() const -> RenderBackendType
    {
        return RenderBackendType::Metal;
    }
}
