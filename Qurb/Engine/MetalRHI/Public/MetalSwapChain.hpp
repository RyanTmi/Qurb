/// \file MetalSwapChain.hpp

#pragma once

#include "MetalDevice.hpp"
#include "MetalRenderTarget.hpp"

#include <Platform/Window.hpp>
#include <RHI/SwapChain.hpp>

#import <Metal/Metal.h>
#import <QuartzCore/QuartzCore.h>

namespace qurb::rhi::metal
{
    class SwapChain final : public rhi::SwapChain
    {
    public:
        using base = rhi::SwapChain;

    public:
        SwapChain(Device* device, const SwapChainDescriptor& descriptor);
        ~SwapChain() override;

    public:
        auto nextRenderTarget() -> RenderTarget* override;

        auto present(id<MTLCommandBuffer> commandBuffer) -> void;
        auto onWindowResize(WindowResizeEvent& e) -> bool;

    private:
        Device*             _device;
        CAMetalLayer*       _layer;
        id<CAMetalDrawable> _currentDrawable;
        RenderTarget*       _renderTarget;
    };
}
