#include "MetalRenderContext.hpp"

namespace qurb::rhi::metal
{
    RenderContext::RenderContext(Device* device, const RenderContextDescriptor& descriptor)
        : base(descriptor)
        , _device(device)
        , _swapChain(nullptr)
        , _currentRenderTarget(nullptr)
        , _framePool(nil)
        , _commandBuffer(nil)
        , _renderCommandEncoder(nil)
        , _frameBoundarySemaphore(dispatch_semaphore_create(3))
    {
        _device->retain();

        _swapChain = static_cast<SwapChain*>(_device->createSwapChain(descriptor.swapChainDescriptor));
    }

    RenderContext::~RenderContext()
    {
        _swapChain->release();
        _device->release();
    }

    auto RenderContext::beginFrame() -> void
    {
        ensure(_framePool == nil, "Frame pool should be nil.");

        dispatch_semaphore_wait(_frameBoundarySemaphore, DISPATCH_TIME_FOREVER);

        _framePool     = [[NSAutoreleasePool alloc] init];
        _commandBuffer = [_device->commandQueue() commandBuffer];
    }

    auto RenderContext::endFrame() -> void
    {
        ensure(_framePool != nil, "Frame pool is nil.");

        [_commandBuffer addCompletedHandler:^(id<MTLCommandBuffer> _Nonnull) { dispatch_semaphore_signal(_frameBoundarySemaphore); }];
        [_commandBuffer commit];
        _commandBuffer = nil;

        [_framePool release];
        _framePool = nil;
    }

    auto RenderContext::present() -> void
    {
        _swapChain->present(_commandBuffer);
    }

    auto RenderContext::beginRenderPass(rhi::RenderTarget* renderTarget, const RenderPassDescriptor& descriptor) -> void
    {
        ensure(_renderCommandEncoder == nil, "Render command encoder is not nil.");

        _currentRenderTarget = static_cast<RenderTarget*>(renderTarget);
        _currentRenderTarget->retain();

        auto* renderPassDescriptor = _currentRenderTarget->renderPassDescriptor(descriptor);
        _renderCommandEncoder      = [_commandBuffer renderCommandEncoderWithDescriptor:renderPassDescriptor];
    }

    auto RenderContext::endRenderPass() -> void
    {
        ensure(_renderCommandEncoder != nil, "Render command encoder is nil.");

        [_renderCommandEncoder endEncoding];
        _renderCommandEncoder = nil;

        _currentRenderTarget->release();
        _currentRenderTarget = nullptr;
    }

    auto RenderContext::pushConstants(const void* data, usize size) -> void
    {
        // NOTE: Assume index = 1 for now
        [_renderCommandEncoder setVertexBytes:data length:size atIndex:1];
    }

    auto RenderContext::bindPipelineState(rhi::PipelineState* pipelineState) -> void
    {
        ensure(_renderCommandEncoder != nil, "Render command encoder is nil.");

        auto* currentPipelineState = static_cast<PipelineState*>(pipelineState);
        currentPipelineState->bind(_currentRenderTarget, _renderCommandEncoder);
    }

    auto RenderContext::bindVertexBuffer(rhi::Buffer* vertexBuffer, uint32 slot, uint32 offset) -> void
    {
        ensure(_renderCommandEncoder != nil, "Render command encoder is nil.");
        ensure(vertexBuffer->type() == BufferType::Vertex, "Binding wrong buffer type.");

        auto* buffer = static_cast<Buffer*>(vertexBuffer);
        if (buffer->isSmallBuffer())
        {
            const auto  length = buffer->size();
            const auto* bytes  = buffer->cpuBuffer();
            [_renderCommandEncoder setVertexBytes:bytes length:length atIndex:slot];
        }
        else
        {
            [_renderCommandEncoder setVertexBuffer:buffer->handle() offset:0 atIndex:slot];
        }
    }

    auto RenderContext::draw(uint32 vertexCount, uint32 firstVertex) -> void
    {
        ensure(_renderCommandEncoder != nil, "Render command encoder is nil.");

        const auto primitive = MTLPrimitiveTypeTriangle;
        [_renderCommandEncoder drawPrimitives:primitive vertexStart:firstVertex vertexCount:vertexCount];
    }

    auto RenderContext::bindFragmentTexture(rhi::Texture* fragmentTexture, uint32 slot) -> void
    {
        ensure(_renderCommandEncoder != nil, "Render command encoder is nil.");

        auto* texture = static_cast<Texture*>(fragmentTexture);

        [_renderCommandEncoder setFragmentTexture:texture->handle() atIndex:slot];
    }
}
