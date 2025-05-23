#include "MetalRenderTarget.hpp"

namespace qurb::rhi::metal
{
    RenderTarget::RenderTarget(Device* device, const RenderTargetDescriptor& descriptor)
        : _device(device)
    {
        _device->retain();
        _colorAttachments.reserve(8);
    }

    RenderTarget::~RenderTarget()
    {
        _device->release();
    }

    auto RenderTarget::setSwapChainTexture(id<MTLTexture> texture, MTLPixelFormat format) -> void
    {
        if (_colorAttachments.empty())
        {
            _colorAttachments.emplaceBack([texture retain], format);
        }
        else
        {
            _colorAttachments[0].texture = texture;
            _colorAttachments[0].format  = format;
        }
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
            const auto[r, g, b, a] = descriptor.clearColor;

            renderPassDescriptor.colorAttachments[i].texture     = _colorAttachments[i].texture;
            renderPassDescriptor.colorAttachments[i].loadAction  = MTLLoadActionClear;
            renderPassDescriptor.colorAttachments[i].storeAction = MTLStoreActionStore;
            renderPassDescriptor.colorAttachments[i].clearColor  = MTLClearColorMake(r, g, b, a);
        }

        if (_depthAttachment.has_value())
        {
            auto& depthAttachment = _depthAttachment.value();
        }

        // TODO: Stencil attachment

        return renderPassDescriptor;
    }
}
