/// \file Buffer.hpp

#pragma once

#include "CoreTypes.hpp"
#include "RHI/Object.hpp"

namespace qurb::rhi
{
    /// \brief The `BufferType` enum.
    enum class BufferType
    {
        None,
        Vertex,
        Index,
        Constant
    };

    /// \brief The `BufferUsage` enum.
    enum class BufferUsage
    {
        None,
        Dynamic,
        Immutable
    };

    /// \brief The `BufferDescriptor` struct.
    struct BufferDescriptor
    {
        const void* initialData;
        usize       bufferSize;
        BufferType  bufferType;
        BufferUsage bufferUsage;
    };

    /// \brief The `Buffer` class.
    class Buffer : public Object
    {
    public:
        explicit Buffer(const BufferDescriptor& descriptor);
        ~Buffer() override = default;

    public:
        [[nodiscard]] auto size() const -> usize;
        [[nodiscard]] auto type() const -> BufferType;
        [[nodiscard]] auto usage() const -> BufferUsage;

        template <typename T>
        auto map() -> T*;

        virtual auto map() -> void*  = 0;
        virtual auto unmap() -> void = 0;

    protected:
        usize       _size;
        BufferType  _type;
        BufferUsage _usage;
    };

    using BufferRef = Ref<Buffer>;

    inline Buffer::Buffer(const BufferDescriptor& descriptor)
        : _size(descriptor.bufferSize)
        , _type(descriptor.bufferType)
        , _usage(descriptor.bufferUsage)
    {}

    inline auto Buffer::size() const -> usize
    {
        return _size;
    }

    inline auto Buffer::type() const -> BufferType
    {
        return _type;
    }

    inline auto Buffer::usage() const -> BufferUsage
    {
        return _usage;
    }

    template <typename T>
    auto Buffer::map() -> T*
    {
        return static_cast<T*>(map());
    }
}
