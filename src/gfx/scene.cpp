#include "scene.h"

#include "camera.h"
#include "shader.h"

#include <glbinding/gl33core/gl.h>

namespace Gfx
{
    using namespace gl33core;

    Scene& Scene::initVAO()
    {
        glGenVertexArrays(1, &vao);
        return *this;
    }

    Scene& Scene::draw(Gfx::Camera &c, Gfx::Shader &s)
    {
        if (vao == 0)
        {
            initVAO();
        }

        glUseProgram(s.program);

        GLint modelLoc = glGetUniformLocation(s.program, "Model");
        GLint viewLoc = glGetUniformLocation(s.program, "View");
        GLint projLoc = glGetUniformLocation(s.program, "Projection");

        glm::mat4 view = c.getView();
        glm::mat4 proj = c.getProjection();

        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, &proj[0][0]);

        glBindVertexArray(vao);
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);

        for(auto &sceneObject : sceneMeshes)
        {
            auto &mesh = loadedMeshes[sceneObject.meshId];
            if (!mesh.gpuData.initialized)
            {
                mesh.update(GL_STATIC_DRAW);
            }
            glBindBuffer(GL_ARRAY_BUFFER, mesh.gpuData.vbuffer);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)offsetof(VertexData, pos));
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)offsetof(VertexData, norm));
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)offsetof(VertexData, uv));
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.gpuData.ibuffer);

            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &sceneObject.transform[0][0]);

            glDrawElements(GL_TRIANGLES, mesh.gpuData.iBufferSize, GL_UNSIGNED_INT, 0);
        }
        return *this;
    }
}
