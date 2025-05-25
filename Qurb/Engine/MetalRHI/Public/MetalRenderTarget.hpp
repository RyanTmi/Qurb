/// \file MetalRenderTarget.hpp

#pragma once

#include "MetalDevice.hpp"

#include <Containers/Vector.hpp>
#include <RHI/RenderTarget.hpp>

#import <Metal/Metal.h>

#include <optional>

namespace qurb::rhi::metal
{
    class RenderTarget : public rhi::RenderTarget
    {
    public:
        using base = rhi::RenderTarget;

    public:
        RenderTarget(Device* device, const RenderTargetDescriptor& descriptor);
        ~RenderTarget() override;

    public:
        auto setSwapChainTexture(id<MTLTexture> texture, MTLPixelFormat format) -> void;
        auto setDepthTexture(id<MTLTexture> texture, MTLPixelFormat format) -> void;
        auto renderPassDescriptor(const RenderPassDescriptor& descriptor) -> MTLRenderPassDescriptor*;

    private:
        friend class PipelineState;

        struct Attachment
        {
            id<MTLTexture> texture;
            MTLPixelFormat format;

        public:
            ~Attachment() { [texture release]; }
        };

    private:
        Device*                   _device;
        Vector<Attachment>        _colorAttachments;
        std::optional<Attachment> _depthAttachment;
    };
}
