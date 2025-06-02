/// \file RenderContext.hpp

#pragma once

#include "CoreTypes.hpp"
#include "RHI/Buffer.hpp"
#include "RHI/Object.hpp"
#include "RHI/PipelineState.hpp"
#include "RHI/RenderPass.hpp"
#include "RHI/RenderTarget.hpp"
#include "RHI/SwapChain.hpp"
#include "RHI/Texture.hpp"

namespace qurb
{
    class Window;
}

namespace qurb::rhi
{
    /// \brief The `RenderContextDescriptor` struct.
    struct RenderContextDescriptor
    {
        SwapChainDescriptor swapChainDescriptor;
    };

    /// \brief The `RenderContext` class.
    class RenderContext : public Object
    {
    public:
        explicit RenderContext(const RenderContextDescriptor& descriptor);
        ~RenderContext() override = default;

    public:
        auto window() const -> Window&;

        virtual auto swapChain() -> SwapChain* = 0;

        virtual auto beginFrame() -> void = 0;
        virtual auto endFrame() -> void   = 0;

        virtual auto present() -> void = 0;

        virtual auto beginRenderPass(RenderTarget* renderTarget) -> void                                         = 0;
        virtual auto beginRenderPass(RenderTarget* renderTarget, const RenderPassDescriptor& descriptor) -> void = 0;
        virtual auto endRenderPass() -> void                                                                     = 0;

        virtual auto pushConstants(const void* data, usize size) -> void = 0;

        virtual auto bindPipelineState(PipelineState* pipelineState) -> void = 0;

        virtual auto bindVertexBuffer(Buffer* vertexBuffer, uint32 slot, uint32 offset) -> void = 0;

        virtual auto bindFragmentTexture(Texture* texture, uint32 slot) -> void = 0;

        virtual auto draw(uint32 vertexCount, uint32 firstVertex) -> void = 0;

    protected:
        Window& _window;
    };

    using RenderContextRef = Ref<RenderContext>;

    inline RenderContext::RenderContext(const RenderContextDescriptor& descriptor)
        : _window(descriptor.swapChainDescriptor.window)
    {}

    inline auto RenderContext::window() const -> Window&
    {
        return _window;
    }
}
