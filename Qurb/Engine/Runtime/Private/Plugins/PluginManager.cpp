#include "Plugins/PluginManager.hpp"

#include "Debug/Ensure.hpp"
#include "Log/Log.hpp"

namespace qurb
{
    using CreatePluginFunction = Plugin* (*) (DynamicLibrary*);

    auto PluginManager::loadPlugins(const Vector<std::string_view>& pluginNames) -> void
    {
        _plugins.clear();
        _plugins.reserve(pluginNames.size());

        for (auto pluginName : pluginNames)
        {
            Plugin* plugin = nullptr;
            {
                auto library      = DynamicLibrary(pluginName);
                auto createPlugin = library.loadFunction<CreatePluginFunction>("createPlugin");

                plugin = createPlugin(&library);
                ensure(plugin != nullptr, "Failed to create plugin: {}", pluginName);

                _plugins.emplaceBack(plugin);
            }

            // Optionally, add and call a boot function of the plugin here.

            Log::info("Plugin '{}' successfully loaded.", pluginName);
        }
    }

    auto PluginManager::getPlugin(std::string_view name) -> Plugin*
    {
        for (auto& plugin : _plugins)
        {
            if (plugin->libraryName() == name or plugin->name() == name)
            {
                return plugin.get();
            }
        }

        return nullptr;
    }

    auto PluginManager::initializePlugins() -> void
    {
        for (auto& plugin : _plugins)
        {
            plugin->initialize();
        }
    }
}
