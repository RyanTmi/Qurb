#include "MetalSwapChain.hpp"

#include <Debug/Ensure.hpp>
#include <Debug/Exceptions.hpp>
#include <Log/Log.hpp>
#include <Platform/MacOS/NativeWindow.hpp>

namespace qurb::rhi::metal
{
    SwapChain::SwapChain(Device* device, const SwapChainDescriptor& descriptor)
        : base(descriptor)
        , _device(device)
        , _layer([descriptor.window.nativeHandle().layer retain])
        , _currentDrawable(nil)
        , _renderTarget(nullptr)
    {
        _device->retain();

        [_layer setDevice:_device->handle()];
        [_layer setFramebufferOnly:YES];
        [_layer setMaximumDrawableCount:3];
        [_layer setPixelFormat:_device->colorBackBufferFormat()];

        _window.registerEvent<WindowResizeEvent>(bind<&SwapChain::onWindowResize>(this));
    }

    SwapChain::~SwapChain()
    {
        _window.unregisterEvent<WindowResizeEvent>(bind<&SwapChain::onWindowResize>(this));

        _device->release();
        [_layer release];
    }

    auto SwapChain::nextRenderTarget() -> RenderTarget*
    {
        _currentDrawable = [_layer nextDrawable];
        auto texture     = [_currentDrawable texture];

        Log::debug("Metal: Drawable ID: {}", _currentDrawable.drawableID);

        return nullptr;
    }

    auto SwapChain::present(id<MTLCommandBuffer> commandBuffer) -> void
    {
        ensure(_currentDrawable != nil, "_currentDrawable is nil, called SwapChain::present before SwapChain::nextRenderTarget.");

        [commandBuffer presentDrawable:_currentDrawable];
        _currentDrawable = nil;
    }

    auto SwapChain::onWindowResize(WindowResizeEvent& e) -> bool
    {
        const auto [width, height] = e.window.size();

        [_layer setDrawableSize:CGSizeMake(width, height)];

        return false;
    }
}
