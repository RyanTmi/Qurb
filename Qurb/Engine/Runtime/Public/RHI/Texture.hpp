/// \file Texture.hpp

#pragma once

#include "CoreTypes.hpp"
#include "RHI/Object.hpp"
#include "RHI/TextureFormat.hpp"

namespace qurb::rhi
{
    /// \brief The `TextureDescriptor` struct.
    struct TextureDescriptor
    {
        uint32        width;
        uint32        height;
        TextureFormat format;
        const uint8*  data;
    };

    /// \brief The `Texture` class.
    class Texture : public Object
    {
    public:
        ~Texture() override = default;
    };

    using TextureRef = Ref<Texture>;
}
