/// \file MetalRenderBackend.hpp

#pragma once

#include <RHI/RenderBackend.hpp>

#import <Foundation/Foundation.h>

namespace qurb::rhi::metal
{
    /// \brief The `RenderBackend` class.
    class RenderBackend final : public rhi::RenderBackend
    {
    public:
        using base = rhi::RenderBackend;

    public:
        RenderBackend();
        ~RenderBackend() override;

    public:
        auto type() const -> RenderBackendType override;
        auto createDevice() const -> rhi::Device* override;

    private:
        NSAutoreleasePool* _autoreleasePool;
    };

    inline RenderBackend::RenderBackend()
        // : _autoreleasePool([[NSAutoreleasePool alloc] init])
        : _autoreleasePool(nil)
    {}

    inline RenderBackend::~RenderBackend()
    {
        // [_autoreleasePool release];
    }

    inline auto RenderBackend::type() const -> RenderBackendType
    {
        return RenderBackendType::Metal;
    }
}
