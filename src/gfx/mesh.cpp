#include "mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <memory>

namespace Gfx
{
    using namespace gl33core;

    Mesh::Mesh()
    {

    }

    Mesh::Mesh(Mesh&& other) noexcept
    {
        gpuData = other.gpuData;
        vertices = std::move(other.vertices);
        indices = std::move(other.indices);
        other.gpuData.initialized = false;
    }

    Mesh& Mesh::update(GLenum usage) {
        if (!gpuData.initialized) {
            glGenBuffers(1, &gpuData.vbuffer);
            glGenBuffers(1, &gpuData.ibuffer);
            gpuData.initialized = true;
        }
        const auto vtxDataSize = vertices.size() * sizeof(vertices[0]);
        const auto idxDataSize = indices.size() * sizeof(indices[0]);

        glBindBuffer(GL_ARRAY_BUFFER, gpuData.vbuffer);
        if (gpuData.vBufferSize < vtxDataSize) {
            glBufferData(GL_ARRAY_BUFFER, vtxDataSize, vertices.data(), usage);
            gpuData.vBufferSize = vtxDataSize;
        } else {
            glBufferSubData(GL_ARRAY_BUFFER, 0, vtxDataSize, vertices.data());
        }

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gpuData.ibuffer);
        if (gpuData.iBufferSize < idxDataSize)
        {
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, idxDataSize, indices.data(), usage);
            gpuData.iBufferSize = idxDataSize;
        }
        else
        {
            glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, idxDataSize, indices.data());
        }
    }

    Mesh::~Mesh()
    {
        if (gpuData.initialized)
        {
            glDeleteBuffers(1, &gpuData.vbuffer);
            glDeleteBuffers(1, &gpuData.ibuffer);
        }
    }

    namespace
    {
        Assimp::Importer *getImporter()
        {
            static std::unique_ptr<Assimp::Importer> aiImporter;
            if (!aiImporter)
            {
                aiImporter = std::make_unique<Assimp::Importer>();
            }
            return aiImporter.get();
        }

    }
}
