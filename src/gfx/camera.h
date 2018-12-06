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
    public:
        Camera() : pos(0.0f), dir(glm::vec3(1.0f, 0.0f, 0.0f)) {}

    };
}

#endif //CMC_CG_TEMPLATE_CAMERA_H
