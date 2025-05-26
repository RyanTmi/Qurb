#pragma once

#include "CoreDefines.hpp"
#include "CoreTypes.hpp"
#include "Math/Matrix4x4.hpp"

namespace qurb
{
    //==================================================================================================================
    // Enum : CameraType
    //==================================================================================================================

    enum class CameraType : uint8
    {
        Orthographic,
        Perspective,
    };

    //==================================================================================================================
    // Class : Camera
    //==================================================================================================================

    class QURB_API Camera
    {
    public:
        Camera() = default;
        Camera(CameraType cameraType, const math::Matrix4x4f& projection);

    public:
        [[nodiscard]] auto view() const -> const math::Matrix4x4f&;
        [[nodiscard]] auto projection() const -> const math::Matrix4x4f&;

    private:
        math::Matrix4x4f _view;
        math::Matrix4x4f _projection;
        CameraType       _cameraType;
    };

    QURB_API auto makeOrthographic(float32 left, float32 right, float32 bottom, float32 top, float32 near, float32 far) -> math::Matrix4x4f;
    QURB_API auto makePerspective(float32 fov, float32 aspect, float32 near, float32 far) -> math::Matrix4x4f;

    //==================================================================================================================
    // Class : Camera
    //==================================================================================================================

    inline Camera::Camera(CameraType cameraType, const math::Matrix4x4f& projection)
        : _view(math::Matrix4x4f::identity)
        , _projection(projection)
        , _cameraType(cameraType)
    {}

    inline auto Camera::view() const -> const math::Matrix4x4f&
    {
        return _view;
    }

    inline auto Camera::projection() const -> const math::Matrix4x4f&
    {
        return _projection;
    }
}
