/// \file RHIPlugin.hpp

#pragma once

#include "Plugins/Plugin.hpp"
#include "RHI/RenderBackend.hpp"

namespace qurb
{
    /// \brief The `RHIPlugin` class.
    class RHIPlugin : public Plugin
    {
    public:
        explicit RHIPlugin(DynamicLibrary&& library);
        virtual ~RHIPlugin() = default;

    public:
        virtual auto createRenderBackend() const -> RenderBackend* = 0;
    };

    inline RHIPlugin::RHIPlugin(DynamicLibrary&& library)
        : Plugin(std::move(library))
    {}
}
