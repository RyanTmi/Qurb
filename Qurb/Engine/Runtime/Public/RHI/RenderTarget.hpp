/// \file RenderTarget.hpp

#pragma once

#include "RHI/Object.hpp"
#include "RHI/RenderPass.hpp"

namespace qurb::rhi
{
    struct RenderTargetDescriptor
    {};

    class RenderTarget : public Object
    {
    public:
        virtual ~RenderTarget() = default;
    };

    using RenderTargetRef = Ref<RenderTarget>;
}
