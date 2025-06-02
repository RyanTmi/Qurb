/// \file Device.hpp

#pragma once

#include "RHI/Buffer.hpp"
#include "RHI/Object.hpp"
#include "RHI/PipelineState.hpp"
#include "RHI/RenderContext.hpp"
#include "RHI/RenderTarget.hpp"
#include "RHI/ShaderProgram.hpp"
#include "RHI/SwapChain.hpp"
#include "RHI/Texture.hpp"

namespace qurb::rhi
{
    /// \brief The `Device` class.
    class Device : public Object
    {
    public:
        ~Device() override = default;

    public:
        virtual auto createRenderContext(const RenderContextDescriptor& descriptor) -> RenderContext* = 0;
        virtual auto createBuffer(const BufferDescriptor& descriptor) -> Buffer*                      = 0;
        virtual auto createRenderTarget(const RenderTargetDescriptor& descriptor) -> RenderTarget*    = 0;
        virtual auto createSwapChain(const SwapChainDescriptor& descriptor) -> SwapChain*             = 0;
        virtual auto createShaderProgram(const ShaderProgramDescriptor& descriptor) -> ShaderProgram* = 0;
        virtual auto createPipelineState(const PipelineStateDescriptor& descriptor) -> PipelineState* = 0;
        virtual auto createTexture(const TextureDescriptor& descriptor) -> Texture*                   = 0;
    };

    using DeviceRef = Ref<Device>;
}
