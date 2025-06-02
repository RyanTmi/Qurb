/// \file RenderTarget.hpp

#pragma once

#include "RHI/Object.hpp"

namespace qurb::rhi
{
    /// \brief The `RenderTargetDescriptor` struct.
    struct RenderTargetDescriptor
    {};

    /// \brief The `RenderTarget` class.
    class RenderTarget : public Object
    {
    public:
        ~RenderTarget() override = default;
    };

    using RenderTargetRef = Ref<RenderTarget>;
}
