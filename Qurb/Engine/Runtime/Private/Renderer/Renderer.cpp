#include "Renderer/Renderer.hpp"

#include "Debug/Ensure.hpp"
#include "Log/Log.hpp"
#include "RHI/RenderContext.hpp"

namespace qurb
{
    auto Renderer::loadBackend(PluginManager& pluginManager, std::string_view backendName) -> void
    {
        ensure(_backendPlugin == nullptr, "Can only load one render backend");

        const auto plugin = pluginManager.getPlugin(backendName);
        if (plugin == nullptr)
        {
            Log::fatal("Failed to find render backend: {}", backendName);
            throw Exception("Failed to load render backend");
        }

        _backendPlugin = static_cast<rhi::Plugin*>(plugin);
        _backend.reset(_backendPlugin->createRenderBackend());
        _device = _backend->createDevice();

        Log::info("Loaded render backend: {}", _backendPlugin->name());
    }

    auto Renderer::onWindowCreate(Window& window) const -> void
    {
        const auto renderContextDescriptor = rhi::RenderContextDescriptor {
            .swapChainDescriptor = rhi::SwapChainDescriptor {.window = window},
        };

        window._renderContext = _device->createRenderContext(renderContextDescriptor);
        window._renderContext->retain();
    }
}
