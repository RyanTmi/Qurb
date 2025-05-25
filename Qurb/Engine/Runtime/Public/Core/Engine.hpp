/// \file Engine.hpp

#pragma once

#include "Core/Application.hpp"
#include "CoreDefines.hpp"
#include "Misc/Clock.hpp"
#include "Platform/Platform.hpp"
#include "Platform/Window.hpp"
#include "Plugins/PluginManager.hpp"
#include "Renderer/Renderer.hpp"

#include <list>
#include <memory>

auto main(int argc, const char** argv) -> int;

namespace qurb
{
    /// \brief The `Engine` class.
    class QURB_API Engine final
    {
    public:
        auto activeWindow() -> Window&;
        auto renderer() -> Renderer&;

    private:
        friend auto ::main(int argc, const char** argv) -> int;

        explicit Engine(Application* application);
        ~Engine();

        auto run() -> void;
        auto createWindow() -> void;
        auto destroyClosedWindows() -> void;
        auto onWindowResize(const WindowResizeEvent& e) -> bool;

    private:
        Platform      _platform;
        Renderer      _renderer;
        PluginManager _pluginManager;

        std::list<Window>            _windows;
        std::unique_ptr<Application> _application;

        Clock _clock;
        bool  _isRunning;
        bool  _isSuspended;
    };

    inline auto Engine::activeWindow() -> Window&
    {
        // TODO: Multi window support
        return _windows.front();
    }

    inline auto Engine::renderer() -> Renderer&
    {
        return _renderer;
    }
}
