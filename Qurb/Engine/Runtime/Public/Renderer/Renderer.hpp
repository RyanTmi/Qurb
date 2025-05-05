/// \file Renderer.hpp

#pragma once

#include "Platform/Window.hpp"
#include "Plugins/PluginManager.hpp"
#include "RHI/RenderBackend.hpp"
#include "RHI/RHIPlugin.hpp"

#include <memory>
#include <string_view>

namespace qurb
{
    class Renderer final
    {
    public:
        Renderer() = default;

    public:
        auto loadBackend(PluginManager& pluginManager, std::string_view backendName) -> void;
        auto onWindowCreate(Window& window) -> void;

    private:
        RHIPlugin*                     _backendPlugin;
        std::unique_ptr<RenderBackend> _backend;
    };
}
