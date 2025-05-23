#include "MetalPipelineState.hpp"

#include <Debug/Ensure.hpp>

#include <ranges>

namespace qurb::rhi::metal
{
    PipelineState::PipelineState(Device* device, const PipelineStateDescriptor& descriptor)
        : base(descriptor)
        , _device(device)
        , _primitiveType(MTLPrimitiveTypeTriangle)
        , _winding(MTLWindingClockwise)
        , _fillMode(MTLTriangleFillModeFill)
        , _cullMode(MTLCullModeBack)
        , _depthBias(0.0f)
        , _slopeScale(0.0f)
        , _depthBiasClamp(0.0f)
        , _depthClipMode(MTLDepthClipModeClip)
        , _depthStencilState(nil)
        , _renderPipelineState(nil)
    {
        _device->retain();
        // primitiveType_ =

        MTLDepthStencilDescriptor* depthStencilDescriptor = [[MTLDepthStencilDescriptor alloc] init];

        // if (descriptor_)
        {
            // [depthStencilDescriptor setDepthCompareFunction: ];
        }

        if (_descriptor.depthStencil.depthTestEnabled)
        {
            [depthStencilDescriptor setDepthWriteEnabled:YES];
        }

        // TODO: To be removed
        [depthStencilDescriptor setDepthWriteEnabled:YES];
        [depthStencilDescriptor setDepthCompareFunction:MTLCompareFunctionLessEqual];

        if (_descriptor.depthStencil.stencilTestEnabled)
        {
            MTLStencilDescriptor* frontFaceStencil = [MTLStencilDescriptor new];
            MTLStencilDescriptor* backFaceStencil  = [MTLStencilDescriptor new];

            [depthStencilDescriptor setFrontFaceStencil:frontFaceStencil];
            [depthStencilDescriptor setBackFaceStencil:backFaceStencil];

            [frontFaceStencil release];
            [backFaceStencil release];
        }

        _depthStencilState = [_device->handle() newDepthStencilStateWithDescriptor:depthStencilDescriptor];
        [depthStencilDescriptor release];
    }

    PipelineState::~PipelineState()
    {
        [_depthStencilState release];
        [_renderPipelineState release];

        _device->release();
    }

    auto PipelineState::bind(RenderTarget* renderTarget, id<MTLRenderCommandEncoder> renderCommandEncoder) -> void
    {
        // renderPipelineStates_.try_emplace(renderTarget, createPipelineState(renderTarget));
        // [renderCommandEncoder setRenderPipelineState:renderPipelineStates_[renderTarget]];

        [_renderPipelineState release];

        _renderPipelineState = createPipelineState(renderTarget);
        [renderCommandEncoder setRenderPipelineState:_renderPipelineState];
        [renderCommandEncoder setDepthStencilState:_depthStencilState];

        // [renderCommandEncoder setStencilReferenceValue:stencilReference_];
        [renderCommandEncoder setFrontFacingWinding:_winding];
        [renderCommandEncoder setCullMode:_cullMode];
        [renderCommandEncoder setDepthBias:_depthBias slopeScale:_slopeScale clamp:_depthBiasClamp];
        [renderCommandEncoder setDepthClipMode:_depthClipMode];
    }

    auto PipelineState::createPipelineState(RenderTarget* renderTarget) -> id<MTLRenderPipelineState>
    {
        auto* shaderProgram = static_cast<ShaderProgram*>(_descriptor.shaderProgram);

        MTLRenderPipelineDescriptor* rpd = [MTLRenderPipelineDescriptor new];
        [rpd setVertexFunction:shaderProgram->vertexFunction()];
        [rpd setFragmentFunction:shaderProgram->fragmentFunction()];
        [rpd setVertexDescriptor:shaderProgram->vertexDescriptor()];

        for (usize i = 0; i < renderTarget->_colorAttachments.size(); ++i)
        {
            const auto& colorAttachment = renderTarget->_colorAttachments[i];

            // Specifying Render Pipeline State
            rpd.colorAttachments[i].pixelFormat = colorAttachment.format;
            if (_attachmentBlendStates.size() <= i)
            {
                continue;
            }
            const auto& blendStates = _attachmentBlendStates[i];

            rpd.colorAttachments[i].writeMask = blendStates.writeMask;

            // Controlling the Blend Operation
            rpd.colorAttachments[i].blendingEnabled     = blendStates.blendingEnabled;
            rpd.colorAttachments[i].alphaBlendOperation = blendStates.alphaBlendOperation;
            rpd.colorAttachments[i].rgbBlendOperation   = blendStates.blendOperation;

            // Specifying Blend Factors
            rpd.colorAttachments[i].destinationAlphaBlendFactor = blendStates.destinationAlphaBlendFactor;
            rpd.colorAttachments[i].destinationRGBBlendFactor   = blendStates.destinationBlendFactor;
            rpd.colorAttachments[i].sourceAlphaBlendFactor      = blendStates.sourceAlphaBlendFactor;
            rpd.colorAttachments[i].sourceRGBBlendFactor        = blendStates.sourceBlendFactor;
        }

        if (renderTarget->_depthAttachment.has_value())
        {
            const auto& depthAttachment = renderTarget->_depthAttachment.value();

            rpd.depthAttachmentPixelFormat = depthAttachment.format;
            // rpd.stencilAttachmentPixelFormat = depthAttachment.format;
        }

        NSError* error = nil;

        id<MTLRenderPipelineState> rps = [_device->handle() newRenderPipelineStateWithDescriptor:rpd error:&error];
        [rpd release];

        ensure(error == nil, "Metal: Failed to create Render Pipeline State.");

        return rps;
    }
}
