#include "MetalTexture.hpp"

#include <Debug/Ensure.hpp>
#include <Log/Log.hpp>

namespace qurb::rhi::metal
{
    auto toMTLPixelFormat(TextureFormat format) -> MTLPixelFormat;

    Texture::Texture(Device* device, const TextureDescriptor& descriptor)
        : _device(device)
        , _handle(nil)
    {
        _device->retain();

        @autoreleasepool
        {
            auto desc = [MTLTextureDescriptor texture2DDescriptorWithPixelFormat:toMTLPixelFormat(descriptor.format)
                                                                           width:descriptor.width
                                                                          height:descriptor.height
                                                                       mipmapped:NO];
            _handle   = [_device->handle() newTextureWithDescriptor:desc];
            ensure(_handle != nil, "Failed to create MTLTexture.");

            if (descriptor.data != nullptr)
            {
                MTLRegion  region      = MTLRegionMake2D(0, 0, descriptor.width, descriptor.height);
                NSUInteger bytesPerRow = 4 * descriptor.width;

                [_handle replaceRegion:region mipmapLevel:0 withBytes:descriptor.data bytesPerRow:bytesPerRow];
            }
        }
    }

    Texture::~Texture()
    {
        [_handle release];
        _device->release();
    }

    inline auto toMTLPixelFormat(TextureFormat format) -> MTLPixelFormat
    {
        switch (format)
        {
            using enum TextureFormat;

            case R8Unorm: return MTLPixelFormatR8Unorm;
            case R8Snorm: return MTLPixelFormatR8Snorm;
            case R8Uint:  return MTLPixelFormatR8Uint;
            case R8Sint:  return MTLPixelFormatR8Sint;

            case RG8Unorm: return MTLPixelFormatRG8Unorm;
            case RG8Snorm: return MTLPixelFormatRG8Snorm;
            case RG8Uint:  return MTLPixelFormatRG8Uint;
            case RG8Sint:  return MTLPixelFormatRG8Sint;

            case RGBA8Unorm: return MTLPixelFormatRGBA8Unorm;
            case RGBA8Snorm: return MTLPixelFormatRGBA8Snorm;
            case RGBA8Uint:  return MTLPixelFormatRGBA8Uint;
            case RGBA8Sint:  return MTLPixelFormatRGBA8Sint;
            case RGBA8Srgb:  return MTLPixelFormatRGBA8Unorm_sRGB;
            case BGRA8Unorm: return MTLPixelFormatBGRA8Unorm;
            case BGRA8Srgb:  return MTLPixelFormatBGRA8Unorm_sRGB;

            case R16Unorm: return MTLPixelFormatR16Unorm;
            case R16Snorm: return MTLPixelFormatR16Snorm;
            case R16Uint:  return MTLPixelFormatR16Uint;
            case R16Sint:  return MTLPixelFormatR16Sint;
            case R16Float: return MTLPixelFormatR16Float;

            case RG16Unorm: return MTLPixelFormatRG16Unorm;
            case RG16Snorm: return MTLPixelFormatRG16Snorm;
            case RG16Uint:  return MTLPixelFormatRG16Uint;
            case RG16Sint:  return MTLPixelFormatRG16Sint;
            case RG16Float: return MTLPixelFormatRG16Float;

            case RGBA16Unorm: return MTLPixelFormatRGBA16Unorm;
            case RGBA16Snorm: return MTLPixelFormatRGBA16Snorm;
            case RGBA16Uint:  return MTLPixelFormatRGBA16Uint;
            case RGBA16Sint:  return MTLPixelFormatRGBA16Sint;
            case RGBA16Float: return MTLPixelFormatRGBA16Float;

            case R32Uint:  return MTLPixelFormatR32Uint;
            case R32Sint:  return MTLPixelFormatR32Sint;
            case R32Float: return MTLPixelFormatR32Float;

            case RG32Uint:  return MTLPixelFormatRG32Uint;
            case RG32Sint:  return MTLPixelFormatRG32Sint;
            case RG32Float: return MTLPixelFormatRG32Float;

            case RGBA32Uint:  return MTLPixelFormatRGBA32Uint;
            case RGBA32Sint:  return MTLPixelFormatRGBA32Sint;
            case RGBA32Float: return MTLPixelFormatRGBA32Float;

            case D16Unorm:        return MTLPixelFormatDepth16Unorm;
            case D24Unorm_S8Uint: return MTLPixelFormatDepth24Unorm_Stencil8;
            case D32Float:        return MTLPixelFormatDepth32Float;
            case D32Float_S8Uint: return MTLPixelFormatDepth32Float_Stencil8;

            default: break;
        }

        Log::error("Invalid pixel format, returning MTLPixelFormatInvalid.");
        return MTLPixelFormatInvalid;
    }
}
