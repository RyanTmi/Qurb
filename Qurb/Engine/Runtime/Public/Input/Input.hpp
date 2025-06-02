/// \file Input.hpp

#pragma once

#include "CoreDefines.hpp"
#include "CoreTypes.hpp"
#include "Input/KeyCode.hpp"
#include "Input/MouseButton.hpp"
#include "Math/Vector2.hpp"

#include <unordered_map>

namespace qurb
{
    /// \brief The `Input` class.
    class QURB_API Input final
    {
    public:
        Input() = delete;

    public:
        static auto isKeyPress(KeyCode key) -> bool;
        static auto isMouseButtonPress(MouseButton button) -> bool;
        static auto mousePosition() -> const math::Vector2f&;
        static auto mouseDelta() -> math::Vector2f;
        
        static auto update() -> void;

        static auto setKeyPress(KeyCode key, bool pressed) -> void;
        static auto setMouseButtonPress(MouseButton button, bool pressed) -> void;
        static auto setMousePosition(math::Vector2f mousePosition) -> void;
        static auto setMouseDelta(math::Vector2f mouseDelta) -> void;

    private:
        static std::unordered_map<KeyCode, bool>     _keys;
        static std::unordered_map<MouseButton, bool> _mouseButtons;
        static math::Vector2f                        _mousePosition;
        static math::Vector2f                        _mouseDelta;
    };
}
