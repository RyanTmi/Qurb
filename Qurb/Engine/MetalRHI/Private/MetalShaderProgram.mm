#include "MetalShaderProgram.hpp"

#include <Debug/Ensure.hpp>

#include <fstream>

namespace qurb::rhi::metal
{
    auto toMTLVertexFormat(ShaderDataType type) -> MTLVertexFormat;

    ShaderProgram::ShaderProgram(Device* device, const ShaderProgramDescriptor& descriptor)
        : base(descriptor)
        , _device(device)
        , _library(nil)
        , _vertexFunction(nil)
        , _fragmentFunction(nil)
        , _vertexDescriptor(nil)
    {
        _device->retain();

        compile();
        createVertexDescriptor();
    }

    ShaderProgram::~ShaderProgram()
    {
        [_vertexDescriptor release];
        [_vertexFunction release];
        [_fragmentFunction release];
        [_library release];

        _device->release();
    }

    auto ShaderProgram::compile() -> void
    {
        @autoreleasepool
        {
            const auto    shaderFileName = descriptor_.shaderName + ".metal";
            std::ifstream shaderFile(shaderFileName);
            ensure(shaderFile.is_open(), "Metal: Could not open shader file {}", shaderFileName);

            std::string sourceCode((std::istreambuf_iterator<char>(shaderFile)), std::istreambuf_iterator<char>());

            MTLCompileOptions* options = [MTLCompileOptions new];
            [options setLanguageVersion:MTLLanguageVersion3_2];

            NSError*  error  = nil;
            NSString* source = [NSString stringWithCString:sourceCode.c_str() encoding:NSUTF8StringEncoding];
            _library         = [_device->handle() newLibraryWithSource:source options:options error:&error];

            if (_library == nil)
            {
                NSString*   stringError  = [NSString stringWithFormat:@"%@", error];
                const char* errorMessage = [stringError cStringUsingEncoding:NSUTF8StringEncoding];

                ensure(false, "Metal: Could not create MTLLibrary from source code: {}", errorMessage);
            }

            {
                const char* functionName = descriptor_.vertexFunctionName.data();
                NSString*   name         = [NSString stringWithCString:functionName encoding:NSUTF8StringEncoding];
                _vertexFunction          = [_library newFunctionWithName:name];

                ensure(_vertexFunction != nil, "Metal: Cannot find {} in the library", functionName);
            }

            {
                const char* functionName = descriptor_.fragmentFunctionName.data();
                NSString*   name         = [NSString stringWithCString:functionName encoding:NSUTF8StringEncoding];
                _fragmentFunction        = [_library newFunctionWithName:name];

                ensure(_fragmentFunction != nil, "Metal: Cannot find {} in the library", functionName);
            }

            [options release];
        }
    }

    auto ShaderProgram::createVertexDescriptor() -> void
    {
        ensure(_vertexDescriptor == nil, "VertexDescriptor is already created.");

        _vertexDescriptor = [MTLVertexDescriptor vertexDescriptor];

        NSUInteger offset = 0;
        for (int32 i = 0; i < descriptor_.bufferLayout.size(); ++i)
        {
            const auto dataType = descriptor_.bufferLayout[i].dataType;

            [_vertexDescriptor.attributes[i] setFormat:toMTLVertexFormat(dataType)];
            [_vertexDescriptor.attributes[i] setBufferIndex:0];
            [_vertexDescriptor.attributes[i] setOffset:offset];

            offset += shaderDataTypeSize(dataType);
        }

        [_vertexDescriptor.layouts[0] setStride:offset];
        [_vertexDescriptor.layouts[0] setStepFunction:MTLVertexStepFunctionPerVertex];
    }

    auto toMTLVertexFormat(ShaderDataType type) -> MTLVertexFormat
    {
        switch (type)
        {
            using enum ShaderDataType;

            case Float:  return MTLVertexFormatFloat;
            case Float2: return MTLVertexFormatFloat2;
            case Float3: return MTLVertexFormatFloat3;
            case Float4: return MTLVertexFormatFloat4;
            case Int:    return MTLVertexFormatInt;
            case Int2:   return MTLVertexFormatInt2;
            case Int3:   return MTLVertexFormatInt3;
            case Int4:   return MTLVertexFormatInt4;
            default:     break;
        }

        ensure(false, "Unknown ShaderDataType");
    }
}
