/// \file RenderBackend.hpp

#pragma once

namespace qurb
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
    };
}
