/// \file MetalDevice.hpp

#pragma once

#include <RHI/Device.hpp>

#import <Metal/Metal.h>

namespace qurb::rhi::metal
{
    /// \brief The `Device` class.
    class Device final : public rhi::Device
    {
    public:
        using base = rhi::Device;

    public:
        Device();
        ~Device() override;

    public:
        auto createRenderContext(const RenderContextDescriptor& descriptor) -> rhi::RenderContext* override;
        auto createBuffer(const BufferDescriptor& descriptor) -> rhi::Buffer* override;
        auto createRenderTarget(const RenderTargetDescriptor& descriptor) -> rhi::RenderTarget* override;
        auto createSwapChain(const SwapChainDescriptor& descriptor) -> rhi::SwapChain* override;
        auto createShaderProgram(const ShaderProgramDescriptor& descriptor) -> rhi::ShaderProgram* override;
        auto createPipelineState(const PipelineStateDescriptor& descriptor) -> rhi::PipelineState* override;
        auto createTexture(const TextureDescriptor& descriptor) -> rhi::Texture* override;

        auto handle() -> id<MTLDevice>;
        auto commandQueue() -> id<MTLCommandQueue>;

        [[nodiscard]] auto colorBackBufferFormat() const -> MTLPixelFormat;
        [[nodiscard]] auto depthBackBufferFormat() const -> MTLPixelFormat;

    private:
        id<MTLDevice>       _handle;
        id<MTLCommandQueue> _commandQueue;
        MTLPixelFormat      _colorBackBufferFormat;
        MTLPixelFormat      _depthBackBufferFormat;
    };

    inline auto Device::handle() -> id<MTLDevice>
    {
        return _handle;
    }

    inline auto Device::commandQueue() -> id<MTLCommandQueue>
    {
        return _commandQueue;
    }

    inline auto Device::colorBackBufferFormat() const -> MTLPixelFormat
    {
        return _colorBackBufferFormat;
    }

    inline auto Device::depthBackBufferFormat() const -> MTLPixelFormat
    {
        return _depthBackBufferFormat;
    }
}
