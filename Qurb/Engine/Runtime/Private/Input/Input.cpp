#include "Input/Input.hpp"

namespace qurb
{
    std::unordered_map<KeyCode, bool>     Input::_keys;
    std::unordered_map<MouseButton, bool> Input::_mouseButtons;
    math::Vector2f                        Input::_mousePosition = math::Vector2f::zero;
    math::Vector2f                        Input::_mouseDelta    = math::Vector2f::zero;

    auto Input::isKeyPress(KeyCode key) -> bool
    {
        return _keys[key];
    }

    auto Input::isMouseButtonPress(MouseButton button) -> bool
    {
        return _mouseButtons[button];
    }

    auto Input::mousePosition() -> const math::Vector2f&
    {
        return _mousePosition;
    }

    auto Input::mouseDelta() -> math::Vector2f
    {
        return _mouseDelta;
    }

    auto Input::update() -> void
    {
        _mouseDelta = math::Vector2f::zero;
    }

    auto Input::setKeyPress(KeyCode key, bool pressed) -> void
    {
        _keys[key] = pressed;
    }

    auto Input::setMouseButtonPress(MouseButton button, bool pressed) -> void
    {
        _mouseButtons[button] = pressed;
    }

    auto Input::setMousePosition(math::Vector2f mousePosition) -> void
    {
        _mouseDelta    = mousePosition - _mousePosition;
        _mousePosition = mousePosition;
    }

    auto Input::setMouseDelta(math::Vector2f mouseDelta) -> void
    {
        _mouseDelta = mouseDelta;
    }
}
