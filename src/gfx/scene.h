#ifndef CMC_CG_TEMPLATE_SCENE_H
#define CMC_CG_TEMPLATE_SCENE_H

#include <vector>
#include "mesh.h"
#include <glbinding/gl33core/gl.h>
#include <glm/mat4x4.hpp>

namespace Gfx
{

    class Camera;
    class Shader;
    using gl33core::GLuint;

    struct SceneObject
    {
        /** Mesh identifier (several placed meshes can share a single Mesh instance ) */
        uint32_t meshId;

        /** Per-object transform matrix */
        glm::mat4 transform;

    };

    class Scene
    {
    private:
        std::vector<Mesh> loadedMeshes;
        std::vector<SceneObject> sceneMeshes;
        GLuint vao;
    public:
        Scene() : vao(0) {}

        Scene& addMesh(Mesh&& loadedMesh) { loadedMeshes.push_back(std::move(loadedMesh)); return *this; }
        Scene& addObject(SceneObject&& object) { sceneMeshes.push_back(object); return *this; }

        Scene& initVAO();

        Scene& draw(Camera &c, Shader &s);
    };

}

#endif //CMC_CG_TEMPLATE_SCENE_H
