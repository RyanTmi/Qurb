#include "Core/Engine.hpp"

#include "Containers/Vector.hpp"
#include "Input/Input.hpp"

namespace qurb
{
    Engine::Engine(Application* application)
        : _application(application)
        , _isRunning(false)
        , _isSuspended(true)
    {
        _application->_engine = this;

        // Plugins to load, should be parsed from a config file.
        const auto pluginsToLoad = Vector<std::string_view> {
            "QurbMetalRHI",
        };
        _pluginManager.loadPlugins(pluginsToLoad);

        _renderer.loadBackend(_pluginManager, "QurbMetalRHI");

        createWindow();

        // Initialize the plugins.
        _pluginManager.initializePlugins();

        // Initialize the application.
        _application->initialize();
    }

    Engine::~Engine()
    {
        _application->shutdown();
    }

    auto Engine::run() -> void
    {
        _isRunning   = true;
        _isSuspended = false;

        auto deltaTime = 0.0f;

        _clock.start();
        while (_isRunning)
        {
            _platform.pollEvents();

            if (_isSuspended)
            {
                continue;
            }

            _clock.update();
            deltaTime = static_cast<float32>(_clock.deltaTime());

            _application->update(deltaTime);
            _application->render();

            // Destroy window that should be closed
            destroyClosedWindows();
            _isRunning = not _windows.empty();

            Input::update();
        }
    }

    auto Engine::createWindow() -> void
    {
        const auto windowDescriptor = WindowDescriptor {
            .title = _application->name(),
            .size  = math::Vector2f(1280.0f, 720.0f),
        };

        auto& window = _windows.emplace_back(windowDescriptor);
        window.registerEvent<WindowResizeEvent>(bind<&Engine::onWindowResize>(this));

        _renderer.onWindowCreate(window);
    }

    auto Engine::destroyClosedWindows() -> void
    {
        for (auto it = _windows.begin(); it != _windows.end();)
        {
            if (it->shouldClose())
            {
                it = _windows.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }

    auto Engine::onWindowResize(const WindowResizeEvent& e) -> bool
    {
        // TODO: Handle multiple windows
        const auto [width, height] = e.window.size();

        _isSuspended = width == 0 or height == 0;

        return false;
    }
}
