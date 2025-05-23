/// \file MetalPipelineState.hpp

#pragma once

#include "Containers/Vector.hpp"
#include "CoreTypes.hpp"
#include "MetalDevice.hpp"
#include "MetalRenderTarget.hpp"
#include "MetalShaderProgram.hpp"
#include "RHI/PipelineState.hpp"

#import <Metal/Metal.h>

#include <unordered_map>

namespace qurb::rhi::metal
{
    class PipelineState final : public rhi::PipelineState
    {
    public:
        using base = rhi::PipelineState;

    public:
        PipelineState(Device* device, const PipelineStateDescriptor& descriptor);
        ~PipelineState() override;

    public:
        // FIXME: Create infinite entries.
        auto bind(RenderTarget* renderTarget, id<MTLRenderCommandEncoder> renderCommandEncoder) -> void;

    private:
        struct AttachmentBlendState
        {
            MTLBlendFactor    sourceBlendFactor;
            MTLBlendFactor    destinationBlendFactor;
            MTLBlendOperation blendOperation;
            MTLBlendFactor    sourceAlphaBlendFactor;
            MTLBlendFactor    destinationAlphaBlendFactor;
            MTLBlendOperation alphaBlendOperation;
            MTLColorWriteMask writeMask;
            bool              blendingEnabled;
        };


    private:
        auto createPipelineState(RenderTarget* renderTarget) -> id<MTLRenderPipelineState>;

    private:
        Device* _device;

        MTLPrimitiveType    _primitiveType;
        MTLWinding          _winding;
        MTLTriangleFillMode _fillMode;
        MTLCullMode         _cullMode;

        Vector<AttachmentBlendState> _attachmentBlendStates;

        float32          _depthBias;
        float32          _slopeScale;
        float32          _depthBiasClamp;
        MTLDepthClipMode _depthClipMode;

        id<MTLDepthStencilState>   _depthStencilState;
        id<MTLRenderPipelineState> _renderPipelineState;
        // std::unordered_map<MetalRenderTarget*, id<MTLRenderPipelineState>> _renderPipelineStates;
    };
}
