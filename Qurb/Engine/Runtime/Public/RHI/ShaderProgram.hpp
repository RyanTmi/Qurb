/// \file ShaderProgram.hpp
///
/// TODO: Read the shader file to infer the bufferLayout automatically.

#pragma once

#include "Containers/Vector.hpp"
#include "RHI/Object.hpp"

#include <string>

namespace qurb::rhi
{
    /// \brief The `ShaderType` enum.
    enum class ShaderType
    {
        Vertex,
        Fragment,
    };

    /// \brief The `ShaderDataType` enum.
    enum class ShaderDataType
    {
        Float,
        Float2,
        Float3,
        Float4,
        Int,
        Int2,
        Int3,
        Int4,
    };

    constexpr auto shaderDataTypeSize(ShaderDataType dataType) -> uint64
    {
        switch (dataType)
        {
            using enum ShaderDataType;

            case Float:  return 1 * 4;
            case Float2: return 2 * 4;
            case Float3: return 3 * 4;
            case Float4: return 4 * 4;
            case Int:    return 1 * 4;
            case Int2:   return 2 * 4;
            case Int3:   return 3 * 4;
            case Int4:   return 4 * 4;
            default:     break;
        }
    }

    /// \brief The `BufferLayoutElement` struct.
    struct BufferLayoutElement
    {
        ShaderDataType dataType;
        std::string    name;
    };

    using BufferLayout = Vector<BufferLayoutElement>;

    /// \brief The `ShaderProgramDescriptor` struct.
    struct ShaderProgramDescriptor
    {
        std::string  shaderName;
        std::string  vertexFunctionName;
        std::string  fragmentFunctionName;
        BufferLayout bufferLayout;
    };

    /// \brief The `ShaderProgram` class.
    class ShaderProgram : public Object
    {
    public:
        explicit ShaderProgram(const ShaderProgramDescriptor& descriptor);
        virtual ~ShaderProgram() = default;

    protected:
        ShaderProgramDescriptor descriptor_;
    };

    using ShaderProgramRef = Ref<ShaderProgram>;

    inline ShaderProgram::ShaderProgram(const ShaderProgramDescriptor& descriptor)
        : descriptor_(descriptor)
    {}
}
