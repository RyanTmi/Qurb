/// \file Plugin.hpp

#pragma once

#include "Plugins/Plugin.hpp"
#include "RHI/RenderBackend.hpp"

namespace qurb::rhi
{
    /// \brief The `Plugin` class.
    class Plugin : public qurb::Plugin
    {
    public:
        using Base = qurb::Plugin;

    public:
        explicit Plugin(DynamicLibrary&& library);
        virtual ~Plugin() = default;

    public:
        virtual auto createRenderBackend() const -> RenderBackend* = 0;
    };

    inline Plugin::Plugin(DynamicLibrary&& library)
        : Base(std::move(library))
    {}
}
