#include "camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Gfx
{
    glm::mat4 Camera::getView()
    {
        return glm::lookAt(pos, pos + dir, glm::vec3(0.0f, 1.0f, 0.0f));
    }

    glm::mat4 Camera::getProjection()
    {
        return glm::perspective(fov, aspect, 0.1f, 100.0f);
    }

    Camera& Camera::move(glm::vec3 direction)
    {
        pos += direction;
        return *this;
    }

    Camera & Camera::moveTo(glm::vec3 newPosition)
    {
        pos = newPosition;
        return *this;
    }

    Camera& Camera::moveForward(float amount)
    {
        pos += amount * dir;
        return *this;
    }

    glm::vec3 direction(float yaw, float pitch)
    {
        using glm::sin;
        using glm::cos;
        return glm::vec3(cos(yaw) * cos(pitch),
                sin(pitch),
                sin(yaw) * cos(pitch)
                );
    }

    Camera& Camera::moveSide(float amount)
    {
        glm::vec3 sideDir = direction(yaw + M_PI_2, pitch);
        pos += amount * sideDir;
        return *this;
    }


    Camera& Camera::rotateX(float amount)
    {
        using glm::sin;
        using glm::cos;
        yaw += amount;
        if (yaw > 2 * M_PI) yaw -= 2 * M_PI;
        if (yaw < -2 * M_PI) yaw += 2 * M_PI;
        dir = direction(yaw, pitch);
        return *this;
    }

    Camera& Camera::rotateY(float amount)
    {
        using glm::sin;
        using glm::cos;
        pitch += amount;
        // Clamp pitch inside a (-PI/2, PI/2) range
        constexpr float MAX_PITCH = 89.0f * float(M_PI / 180);

        if (pitch > MAX_PITCH) pitch = MAX_PITCH;
        if (pitch < -MAX_PITCH) pitch = -MAX_PITCH;
        dir = direction(yaw, pitch);
        return *this;
    }


}

