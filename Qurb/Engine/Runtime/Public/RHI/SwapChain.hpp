/// \file SwapChain.hpp

#pragma once

#include "RHI/Object.hpp"
#include "RHI/RenderTarget.hpp"

namespace qurb
{
    class Window;
}

namespace qurb::rhi
{
    /// \brief The `SwapChainDescriptor` struct.
    struct SwapChainDescriptor
    {
        Window& window;
    };

    /// \brief The `SwapChain` class.
    class SwapChain : public Object
    {
    public:
        explicit SwapChain(const SwapChainDescriptor& descriptor);
        ~SwapChain() override = default;

    public:
        virtual auto nextRenderTarget() -> RenderTarget* = 0;

    protected:
        Window& _window;
    };

    using SwapChainRef = Ref<SwapChain>;

    inline SwapChain::SwapChain(const SwapChainDescriptor& descriptor)
        : _window(descriptor.window)
    {}
}
