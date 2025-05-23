#include "MetalRenderTarget.hpp"

namespace qurb::rhi::metal
{
    RenderTarget::RenderTarget(Device* device, const RenderTargetDescriptor& descriptor)
        : _device(device)
    {
        _device->retain();
        _colorAttachments.resize(8);
    }

    RenderTarget::~RenderTarget()
    {
        _device->release();
    }

    auto RenderTarget::setSwapChainTexture(id<MTLTexture> texture, MTLPixelFormat format) -> void
    {
        _colorAttachments[0].texture = [texture retain];
        _colorAttachments[0].format  = format;
    }

    auto RenderTarget::setDepthTexture(id<MTLTexture> texture, MTLPixelFormat format) -> void
    {
        _depthAttachment.reset();
        _depthAttachment = Attachment(texture, format);
    }

    auto RenderTarget::renderPassDescriptor(const RenderPassDescriptor& descriptor) -> MTLRenderPassDescriptor*
    {
        MTLRenderPassDescriptor* renderPassDescriptor = [MTLRenderPassDescriptor renderPassDescriptor];

        for (usize i = 0; i < _colorAttachments.size(); ++i)
        {
            renderPassDescriptor.colorAttachments[i].texture = _colorAttachments[i].texture;
            // renderPassDescriptor.colorAttachments[i].loadAction = ;
            // renderPassDescriptor.colorAttachments[i].storeAction = ;
            // renderPassDescriptor.colorAttachments[i].clearColor = ;
        }

        if (_depthAttachment.has_value())
        {
            auto& depthAttachment = _depthAttachment.value();
        }

        // TODO: Stencil attachment

        return renderPassDescriptor;
    }
}
