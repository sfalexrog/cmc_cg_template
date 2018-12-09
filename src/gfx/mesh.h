#ifndef CMC_CG_TEMPLATE_MESH_H
#define CMC_CG_TEMPLATE_MESH_H

#include <vector>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <cstdint>

#include <glbinding/gl33core/gl.h>

namespace Gfx
{
    using gl33core::GLuint;
    using gl33core::GLenum;
    using gl33core::GL_STATIC_DRAW;

    struct VertexData
    {
        /** Vertex position */
        glm::vec3 pos;
        /** Vertex normal */
        glm::vec3 norm;
        /** Texture UV coordinates */
        glm::vec2 uv;
    };

    struct MeshGpuData
    {
        /** True if vertex and index buffers are generated, false otherwise */
        bool initialized;
        /** Vertex buffer object (with vertex data) */
        GLuint vbuffer;
        /** Index buffer object (with triangle indices)*/
        GLuint ibuffer;

        /** Allocated GPU vertex buffer size */
        GLuint vBufferSize;
        /** Allocated GPU index buffer size*/
        GLuint iBufferSize;

        MeshGpuData() : initialized(false), vbuffer(0), ibuffer(0), vBufferSize(0), iBufferSize(0) {}
    };


    class Mesh
    {
    public:
        /** In-memory vertex storage */
        std::vector<VertexData> vertices;
        /** In-memory index storage */
        std::vector<std::uint32_t> indices;

        /** GPU-specific data for renderer */
        MeshGpuData gpuData;

        /** Create an empty mesh (no vertices, no indices) */
        Mesh();


        /** Move constructor - should allow us to pass mesh around and not worry about losing our precious GPU data */
        Mesh(Mesh&& other) noexcept;

        /** Update gpu data with what's in our CPU memory */
        Mesh& update(GLenum usage = GL_STATIC_DRAW);

        ~Mesh();
    };
}

#endif //CMC_CG_TEMPLATE_MESH_H
