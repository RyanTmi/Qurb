#pragma once

#include "MetalDevice.hpp"

#include <RHI/ShaderProgram.hpp>

#import <Metal/Metal.h>

namespace qurb::rhi::metal
{
    class ShaderProgram final : public rhi::ShaderProgram
    {
    public:
        using base = rhi::ShaderProgram;

    public:
        ShaderProgram(Device* device, const ShaderProgramDescriptor& descriptor);
        ~ShaderProgram() override;

    public:
        auto vertexFunction() const -> id<MTLFunction>;
        auto fragmentFunction() const -> id<MTLFunction>;
        auto vertexDescriptor() const -> MTLVertexDescriptor*;

    private:
        auto compile() -> void;
        auto createVertexDescriptor() -> void;

    private:
        Device*              _device;
        id<MTLLibrary>       _library;
        id<MTLFunction>      _vertexFunction;
        id<MTLFunction>      _fragmentFunction;
        MTLVertexDescriptor* _vertexDescriptor;
    };

    inline auto ShaderProgram::vertexFunction() const -> id<MTLFunction>
    {
        return _vertexFunction;
    }

    inline auto ShaderProgram::fragmentFunction() const -> id<MTLFunction>
    {
        return _fragmentFunction;
    }

    inline auto ShaderProgram::vertexDescriptor() const -> MTLVertexDescriptor*
    {
        return _vertexDescriptor;
    }
}
