/// \file Renderer.hpp

#pragma once

#include "Platform/Window.hpp"
#include "Plugins/PluginManager.hpp"
#include "RHI/Device.hpp"
#include "RHI/Plugin.hpp"
#include "RHI/RenderBackend.hpp"

#include <memory>
#include <string_view>

namespace qurb
{
    class Renderer final
    {
    public:
        Renderer();

    public:
        auto device() -> rhi::Device*;

        auto loadBackend(PluginManager& pluginManager, std::string_view backendName) -> void;
        auto onWindowCreate(Window& window) -> void;

    private:
        rhi::Plugin*                        _backendPlugin;
        std::unique_ptr<rhi::RenderBackend> _backend;
        rhi::Device*                        _device;
    };

    inline Renderer::Renderer()
        : _backendPlugin(nullptr)
        , _backend(nullptr)
        , _device(nullptr)
    {}

    inline auto Renderer::device() -> rhi::Device*
    {
        return _device;
    }
}
