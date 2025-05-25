/// \file PipelineState.hpp

#pragma once

#include "Containers/Vector.hpp"
#include "RHI/Object.hpp"

#include <bitset>

namespace qurb::rhi
{
    class ShaderProgram;

    /// \brief The `PrimitiveTopology` enum.
    enum class PrimitiveTopology
    {
        None,
        Point,
        Line,
        LineStrip,
        Triangle,
        TriangleStrip,
    };

    /// \brief The `PrimitiveType` enum.
    enum class PrimitiveType
    {
        None,
        Point,
        Line,
        LineStrip,
        Triangle,
        TriangleStrip
    };

    /// \brief The `TriangleFillMode` enum.
    enum class TriangleFillMode
    {
        None,
        Solid,
        WireFrame
    };

    /// \brief The `CullMode` enum.
    enum class CullMode
    {
        None,
        Front,
        Back
    };

    /// \brief The `StencilOperation` enum.
    enum class StencilOperation
    {
        None,
        Keep,
        Zero,
        Replace,
        IncrementClamp,
        DecrementClamp,
        Invert,
        IncrementWrap,
        DecrementWrap
    };

    /// \brief The `CompareFunction` enum.
    enum class CompareFunction
    {
        None,
        Never,
        Less,
        Equal,
        LessEqual,
        Greater,
        NotEqual,
        GreaterEqual,
        Always
    };

    /// \brief The `Blend` enum.
    enum class Blend
    {
        None,
        Zero,
        One,
        SourceColor,
        OneMinusSourceColor,
        SourceAlpha,
        OneMinusSourceAlpha,
        DestinationColor,
        OneMinusDestinationColor,
        DestinationAlpha,
        OneMinusDestinationAlpha,
        SourceAlphaSaturated,
    };

    /// \brief The `BlendOperation` enum.
    enum class BlendOperation
    {
        None,
        Add,
        Subtract,
        ReverseSubtract,
        Min,
        Max
    };

    /// \brief The `TextureFilter` enum.
    enum class TextureFilter
    {
        None,
        Nearest,
        Linear
    };

    /// \brief The `SamplerMipmapMode` enum.
    enum class SamplerMipmapMode
    {
        None,
        Nearest,
        Linear
    };

    /// \brief The `SamplerAddressMode` enum.
    enum class SamplerAddressMode
    {
        None,
        Repeat,
        MirrorRepeat,
        MirrorClampToEdge,
        ClampToEdge,
        ClampToZero,
        ClampToBorder,
    };

    /// \brief The `DepthStencilOperationDescriptor` struct.
    struct DepthStencilOperationDescriptor
    {
        StencilOperation stencilFailOp;
        StencilOperation depthFailOp;
        StencilOperation passOp;
        CompareFunction  stencilFunc;
        uint8            readMask;
        uint8            writeMask;
        uint32           reference;
    };

    /// \brief The `DepthStencilDescriptor` struct.
    struct DepthStencilDescriptor
    {
        bool                            depthTestEnabled;
        bool                            depthWriteEnabled;
        CompareFunction                 depthFunction;
        bool                            stencilTestEnabled;
        DepthStencilOperationDescriptor frontFace;
        DepthStencilOperationDescriptor backFace;
    };

    /// \brief The `RasterizerDescriptor` struct.
    struct RasterizerDescriptor
    {
        TriangleFillMode fillMode;
        CullMode         cullMode;
        int32            depthBias;
        float32          depthBiasClamp;
        float32          slopeScaleDepthBias;
        bool             depthClipEnabled;
        bool             scissorTestEnabled;
    };

    /// \brief The `RenderTargetBlendDescriptor` struct.
    struct RenderTargetBlendDescriptor
    {
        Blend          sourceBlend;
        Blend          destinationBlend;
        BlendOperation blendOperation;
        Blend          sourceAlphaBlend;
        Blend          destinationAlphaBlend;
        BlendOperation alphaBlendOperation;
        std::bitset<4> writeMask;
        bool           blendingEnabled;
    };

    /// \brief The `BlendDescriptor` struct.
    struct BlendDescriptor
    {
        Vector<RenderTargetBlendDescriptor> renderTargets;
    };

    /// \brief The `PipelineStateDescriptor` struct.
    struct PipelineStateDescriptor
    {
        PrimitiveTopology      primitiveTopology;
        DepthStencilDescriptor depthStencil;
        RasterizerDescriptor   rasterizer;
        BlendDescriptor        blend;
        ShaderProgram*         shaderProgram;
    };

    /// \brief The `PipelineState` class.
    class PipelineState : public Object
    {
    public:
        explicit PipelineState(const PipelineStateDescriptor& descriptor);

        virtual ~PipelineState() = default;

    protected:
        PipelineStateDescriptor _descriptor;
    };

    using PipelineStateRef = Ref<PipelineState>;

    inline PipelineState::PipelineState(const PipelineStateDescriptor& descriptor)
        : _descriptor(descriptor)
    {}
}
