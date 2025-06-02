/// \file Renderer.hpp

#pragma once

#include "Assets/TextureManager.hpp"
#include "Platform/Window.hpp"
#include "Plugins/PluginManager.hpp"
#include "RHI/Device.hpp"
#include "RHI/Plugin.hpp"
#include "RHI/RenderBackend.hpp"

#include <memory>
#include <string_view>

namespace qurb
{
    /// \brief The `Renderer` class.
    class Renderer final
    {
    public:
        Renderer();

    public:
        auto device() const -> rhi::Device*;
        auto textureManager() -> TextureManager&;

        auto loadBackend(PluginManager& pluginManager, std::string_view backendName) -> void;
        auto onWindowCreate(Window& window) const -> void;

    private:
        rhi::Plugin*                        _backendPlugin;
        std::unique_ptr<rhi::RenderBackend> _backend;
        rhi::Device*                        _device;
        TextureManager                      _textureManager;
    };

    inline Renderer::Renderer()
        : _backendPlugin(nullptr)
        , _backend(nullptr)
        , _device(nullptr)
        , _textureManager(*this)
    {}

    inline auto Renderer::device() const -> rhi::Device*
    {
        return _device;
    }

    inline auto Renderer::textureManager() -> TextureManager&
    {
        return _textureManager;
    }
}
