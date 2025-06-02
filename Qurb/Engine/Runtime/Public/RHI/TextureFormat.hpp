/// \file TextureFormat.hpp

#pragma once

namespace qurb::rhi
{
    /// \brief The `TextureFormat` enum.
    enum class TextureFormat
    {
        Unknown,

        // 8-bit formats
        R8Unorm,
        R8Snorm,
        R8Uint,
        R8Sint,

        // 16-bit formats (2 channels)
        RG8Unorm,
        RG8Snorm,
        RG8Uint,
        RG8Sint,

        // 32-bit formats (RGBA8)
        RGBA8Unorm,
        RGBA8Snorm,
        RGBA8Uint,
        RGBA8Sint,
        RGBA8Srgb,
        BGRA8Unorm,
        BGRA8Srgb,

        // 16-bit per channel formats
        R16Unorm,
        R16Snorm,
        R16Uint,
        R16Sint,
        R16Float,

        RG16Unorm,
        RG16Snorm,
        RG16Uint,
        RG16Sint,
        RG16Float,

        RGBA16Unorm,
        RGBA16Snorm,
        RGBA16Uint,
        RGBA16Sint,
        RGBA16Float,

        // 32-bit formats (single channel and multichannel)
        R32Uint,
        R32Sint,
        R32Float,

        RG32Uint,
        RG32Sint,
        RG32Float,

        RGBA32Uint,
        RGBA32Sint,
        RGBA32Float,

        // Depth-stencil formats
        D16Unorm,
        D24Unorm_S8Uint,
        D32Float,
        D32Float_S8Uint,
    };
}
