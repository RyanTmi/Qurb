/// \file Components.hpp

#pragma once

#include "Math/Matrix4x4.hpp"
#include "Math/Vector3.hpp"

namespace qurb
{
    struct TagComponent
    {
        std::string name;

    public:
        TagComponent()                    = default;
        TagComponent(const TagComponent&) = default;
        TagComponent(TagComponent&&)      = default;
    };

    struct TransformComponent
    {
        math::Vector3f position;
        math::Vector3f rotation;
        math::Vector3f scale;

    public:
        TransformComponent() = default;

    public:
        [[nodiscard]] auto transformMatrix() -> const math::Matrix4x4f&;

    private:
        math::Matrix4x4f _transform;
    };

    inline auto TransformComponent::transformMatrix() -> const math::Matrix4x4f&
    {
        _transform = translationMatrix(position);
        _transform *= scaleMatrix(scale);
        _transform *= rotationMatrix(rotation);
        return _transform;
    }

    struct NativeScriptComponent
    {
        NativeScriptComponent()          = default;
        virtual ~NativeScriptComponent() = default;

    protected:
        virtual auto start() -> void                   = 0;
        virtual auto update(float32 deltaTime) -> void = 0;
        virtual auto destroy() -> void                 = 0;
    };
}
