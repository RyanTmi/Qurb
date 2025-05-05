#include "Renderer/Renderer.hpp"

#include "Debug/Ensure.hpp"
#include "Log/Log.hpp"

namespace qurb
{
    auto Renderer::loadBackend(PluginManager& pluginManager, std::string_view backendName) -> void
    {
        auto plugin = pluginManager.getPlugin(backendName);
        ensure(plugin != nullptr, "Failed to load plugin: {}", backendName);

        _backendPlugin = static_cast<RHIPlugin*>(plugin);
        _backend.reset(_backendPlugin->createRenderBackend());

        Log::info("Loaded render backend: {}", _backendPlugin->name());
    }

    auto Renderer::onWindowCreate(Window& window) -> void {}
}
