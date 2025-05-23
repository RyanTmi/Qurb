/// \file MetalBuffer.hpp

#pragma once

#include "MetalDevice.hpp"

#include <RHI/Buffer.hpp>

#import <Metal/Metal.h>

namespace qurb::rhi::metal
{
    /// \brief The `Buffer` class.
    class Buffer final : public rhi::Buffer
    {
    public:
        using Base = rhi::Buffer;

    public:
        Buffer(Device* device, const BufferDescriptor& descriptor);
        ~Buffer() override;

    public:
        auto map() -> void* override;
        auto unmap() -> void override;

        auto               handle() -> id<MTLBuffer>;
        [[nodiscard]] auto cpuBuffer() -> void*;
        [[nodiscard]] auto cpuBuffer() const -> const void*;

        [[nodiscard]] auto isSmallBuffer() const -> bool;

    private:
        Device*       _device;
        id<MTLBuffer> _handle;
        void*         _cpuBuffer;
        bool          _isSmallBuffer;
    };

    inline auto Buffer::handle() -> id<MTLBuffer>
    {
        return _handle;
    }

    inline auto Buffer::cpuBuffer() -> void*
    {
        return _cpuBuffer;
    }

    inline auto Buffer::cpuBuffer() const -> const void*
    {
        return _cpuBuffer;
    }

    inline auto Buffer::isSmallBuffer() const -> bool
    {
        return _isSmallBuffer;
    }
}
