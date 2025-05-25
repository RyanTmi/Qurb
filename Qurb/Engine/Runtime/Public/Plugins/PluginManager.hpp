#pragma once

#include "Containers/Vector.hpp"
#include "Plugins/Plugin.hpp"

#include <memory>

namespace qurb
{
    class PluginManager
    {
    public:
        PluginManager() = default;

        PluginManager(const PluginManager&)                    = delete;
        auto operator=(const PluginManager&) -> PluginManager& = delete;

    public:
        auto loadPlugins(const Vector<std::string_view>& pluginNames) -> void;
        auto getPlugin(std::string_view name) -> Plugin*;

        auto initializePlugins() -> void;

    private:
        Vector<std::unique_ptr<Plugin>> _plugins;
    };
}
