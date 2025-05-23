/// \file RenderPass.hpp

#pragma once

#include "Renderer/Color.hpp"

namespace qurb::rhi
{
    /// \brief The `RenderPassDescriptor` struct.
    struct RenderPassDescriptor
    {
        Color clearColor = Color::black;
    };
}
