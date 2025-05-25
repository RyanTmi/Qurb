/// \file MetalTexture.hpp

#pragma once

#include "MetalDevice.hpp"

#include <RHI/Texture.hpp>

#import <Metal/Metal.h>

namespace qurb::rhi::metal
{
    /// \brief The `Texture` class.
    class Texture final : public rhi::Texture
    {
    public:
        using base = rhi::Texture;

    public:
        Texture(Device* device, const TextureDescriptor& descriptor);
        ~Texture() override;

    public:
        [[nodiscard]] auto handle() const -> id<MTLTexture>;

    private:
        Device*        _device;
        id<MTLTexture> _handle;
    };

    inline auto Texture::handle() const -> id<MTLTexture>
    {
        return _handle;
    }
}
