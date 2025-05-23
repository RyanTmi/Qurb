#include "MetalDevice.hpp"

#include "MetalBuffer.hpp"
#include "MetalPipelineState.hpp"
#include "MetalRenderContext.hpp"
#include "MetalRenderTarget.hpp"
#include "MetalShaderProgram.hpp"
#include "MetalSwapChain.hpp"
#include "MetalTexture.hpp"

#include <Debug/Ensure.hpp>

namespace qurb::rhi::metal
{
    Device::Device()
        : _handle(MTLCreateSystemDefaultDevice())
        , _commandQueue(nil)
        , _colorBackBufferFormat(MTLPixelFormatBGRA8Unorm_sRGB)
        , _depthBackBufferFormat(MTLPixelFormatDepth32Float)
    {
        ensure(_handle != nil, "Failed to create system default device.");

        _commandQueue = [_handle newCommandQueue];
        ensure(_commandQueue != nil, "Failed to create command queue.");
    }

    Device::~Device()
    {
        [_commandQueue release];
        [_handle release];
    }

    auto Device::createRenderContext(const RenderContextDescriptor& descriptor) -> rhi::RenderContext*
    {
        return new RenderContext(this, descriptor);
    }

    auto Device::createBuffer(const BufferDescriptor& descriptor) -> rhi::Buffer*
    {
        return new Buffer(this, descriptor);
    }

    auto Device::createRenderTarget(const RenderTargetDescriptor& descriptor) -> rhi::RenderTarget*
    {
        return new RenderTarget(this, descriptor);
    }

    auto Device::createSwapChain(const SwapChainDescriptor& descriptor) -> rhi::SwapChain*
    {
        return new SwapChain(this, descriptor);
    }

    auto Device::createShaderProgram(const ShaderProgramDescriptor& descriptor) -> rhi::ShaderProgram*
    {
        return new ShaderProgram(this, descriptor);
    }

    auto Device::createPipelineState(const PipelineStateDescriptor& descriptor) -> rhi::PipelineState*
    {
        return new PipelineState(this, descriptor);
    }

    auto Device::createTexture(const TextureDescriptor& descriptor) -> rhi::Texture*
    {
        return new Texture(this, descriptor);
    }
}
