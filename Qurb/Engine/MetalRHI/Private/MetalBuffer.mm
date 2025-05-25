#include "MetalBuffer.hpp"

#include <Debug/Ensure.hpp>
#include <Log/Log.hpp>

namespace qurb::rhi::metal
{
    Buffer::Buffer(Device* device, const BufferDescriptor& descriptor)
        : Base(descriptor)
        , _device(device)
        , _handle(nil)
        , _cpuBuffer(nullptr)
        , _isSmallBuffer(false)
    {
        _device->retain();

        ensure(_size > 0, "Cannot create a zero size Buffer.");

        _cpuBuffer = ::operator new(_size);
        if (descriptor.initialData != nullptr)
        {
            std::memcpy(_cpuBuffer, descriptor.initialData, _size);
        }

        if (not _isSmallBuffer)
        {
            if (_usage == BufferUsage::Immutable)
            {
                ensure(descriptor.initialData != nullptr, "Immutable buffer requires initial data.");
            }

            MTLResourceOptions resourceOptions = MTLResourceStorageModeShared;
            if (descriptor.initialData != nullptr)
            {
                _handle = [_device->handle() newBufferWithBytes:descriptor.initialData length:_size options:resourceOptions];
            }
            else
            {
                _handle = [_device->handle() newBufferWithLength:_size options:resourceOptions];
            }
        }
    }

    Buffer::~Buffer()
    {
        if (not _isSmallBuffer)
        {
            [_handle release];
        }

        ::operator delete(_cpuBuffer, _size);
        _device->release();
    }

    auto Buffer::map() -> void*
    {
        if (_usage == BufferUsage::Immutable)
        {
            Log::warn("Cannot map an immutable buffer");
            return nullptr;
        }

        return _cpuBuffer;
    }

    auto Buffer::unmap() -> void
    {
        if (_usage == BufferUsage::Immutable)
        {
            Log::warn("Cannot unmap an immutable buffer");
            return;
        }

        std::memcpy([_handle contents], _cpuBuffer, _size);
    }
}
