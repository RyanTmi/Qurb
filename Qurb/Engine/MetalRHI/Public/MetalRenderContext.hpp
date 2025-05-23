/// \file MetalRenderContext.hpp

#pragma once

#include "MetalBuffer.hpp"
#include "MetalDevice.hpp"
#include "MetalPipelineState.hpp"
#include "MetalRenderTarget.hpp"
#include "MetalShaderProgram.hpp"
#include "MetalSwapChain.hpp"
#include "MetalTexture.hpp"

#include <RHI/RenderContext.hpp>

namespace qurb::rhi::metal
{
    /// \brief The `RenderContext` class.
    class RenderContext final : public rhi::RenderContext
    {
    public:
        using base = rhi::RenderContext;

    public:
        RenderContext(Device* device, const RenderContextDescriptor& descriptor);
        ~RenderContext() override;

    public:
        auto beginFrame() -> void override;
        auto endFrame() -> void override;

        auto present() -> void override;

        auto beginRenderPass(rhi::RenderTarget* renderTarget, const RenderPassDescriptor& descriptor) -> void override;
        auto endRenderPass() -> void override;

        auto bindPipelineState(rhi::PipelineState* pipelineState) -> void override;

        auto bindVertexBuffer(rhi::Buffer* vertexBuffer, uint32 slot, uint32 offset) -> void override;

        auto bindFragmentTexture(rhi::Texture* texture, uint32 slot) -> void override;

        auto draw(uint32 vertexCount, uint32 firstVertex) -> void override;

    private:
        Device*                     _device;
        SwapChain*                  _swapChain;
        RenderTarget*               _currentRenderTarget;
        NSAutoreleasePool*          _framePool;
        id<MTLCommandBuffer>        _commandBuffer;
        id<MTLRenderCommandEncoder> _renderCommandEncoder;
        dispatch_semaphore_t        _frameBoundarySemaphore;
    };
}
