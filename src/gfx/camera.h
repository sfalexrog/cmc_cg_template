#ifndef CMC_CG_TEMPLATE_CAMERA_H
#define CMC_CG_TEMPLATE_CAMERA_H

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

namespace Gfx
{
    class Camera
    {
    private:
        glm::vec3 pos;
        glm::vec3 dir;
        float fov;
        float aspect;

        float yaw;
        float pitch;

    public:
        Camera() : pos(0.0f), dir(glm::vec3(1.0f, 0.0f, 0.0f)), fov(90.0f * M_PI / 180), aspect(1.0f), yaw(0.0f), pitch(0.0f) {}

        Camera& setAspect(float newAspect)
        {
            aspect = newAspect;
            return *this;
        }

        Camera& setFov(float newFov)
        {
            fov = newFov;
            return *this;
        }

        Camera& move(glm::vec3 direction);
        Camera& moveTo(glm::vec3 newPosition);
        Camera& moveForward(float amount);
        Camera& moveSide(float amount);

        Camera& rotateX(float amount);
        Camera& rotateY(float amount);

        glm::mat4 getView();
        glm::mat4 getProjection();
    };
}

#endif //CMC_CG_TEMPLATE_CAMERA_H
