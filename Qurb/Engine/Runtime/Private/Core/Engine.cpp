#include "Core/Engine.hpp"

namespace qurb
{
    Engine::Engine(Application* application)
        : _platform()
        , _renderer()
        , _application(application)
        , _isRunning(false)
        , _isSuspended(false)
    {
        createWindow();

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
            deltaTime = _clock.deltaTime();

            _application->update(deltaTime);

            // Destroy window that should be closed
            destroyClosedWindows();
            _isRunning = not _windows.empty();
        }
    }

    auto Engine::createWindow() -> void
    {
        const auto windowDescriptor = WindowDescriptor {
            .name = _application->descriptor().name,
        };

        auto& window = _windows.emplace_back(windowDescriptor);
        window.listenEvent<WindowResizeEvent>(bind<&Engine::onWindowResize>(this));
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
        _isSuspended = e.width == 0 or e.height == 0;

        return false;
    }
}
