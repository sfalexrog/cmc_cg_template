#include "sceneloader.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "gfx/mesh.h"
#include "gfx/scene.h"

#include "logger.h"

using namespace Gfx;

Scene loadSceneFromFile(const char* filename)
{
    Assimp::Importer importer;
    Scene gfxScene;

    Log(S_DEBUG) << "Loading scene from " << filename;

    const aiScene *scene = importer.ReadFile(filename,
            aiProcess_Triangulate |
            aiProcess_OptimizeMeshes |
            aiProcess_OptimizeGraph |
            aiProcess_GenNormals
            );

    if (scene->mRootNode)
    {
        Log(S_DEBUG) << "Loaded scene; mesh count: " << scene->mNumMeshes
                     << ", texture count: " << scene->mNumTextures
                     << ", material count: " << scene->mNumMaterials
                     << ", root node name: " << scene->mRootNode->mName.C_Str();

        for(int meshId = 0; meshId < scene->mNumMeshes; ++meshId)
        {
            auto *aMesh = scene->mMeshes[meshId];
            Log(S_DEBUG) << "Loading mesh " << aMesh->mName.C_Str()
                         << ": " << aMesh->mNumVertices << " vertices, "
                         << aMesh->mNumFaces << " faces, "
                         << aMesh->mNumUVComponents[0] << " UV components";
            Mesh gfxMesh;
            for(int vtx = 0; vtx < aMesh->mNumVertices; ++vtx)
            {
                VertexData vd{};
                vd.pos = glm::vec3{aMesh->mVertices[vtx].x,
                                   aMesh->mVertices[vtx].y,
                                   aMesh->mVertices[vtx].z};
                vd.norm = glm::vec3{aMesh->mNormals[vtx].x,
                                    aMesh->mNormals[vtx].y,
                                    aMesh->mNormals[vtx].z};
                vd.uv = glm::vec2{aMesh->mTextureCoords[0]->x,
                                  aMesh->mTextureCoords[0]->y};
                gfxMesh.vertices.push_back(vd);
            }
            for(int idx = 0; idx < aMesh->mNumFaces; ++idx)
            {
                // Assume we have three indices per face; aiProcess_triangulate should guarantee that
                gfxMesh.indices.push_back(aMesh->mFaces[idx].mIndices[0]);
                gfxMesh.indices.push_back(aMesh->mFaces[idx].mIndices[1]);
                gfxMesh.indices.push_back(aMesh->mFaces[idx].mIndices[2]);
            }
            gfxScene.addMesh(std::move(gfxMesh));
        }

        // Traverse nodes; for now we just have to worry about the topmost node, so a todo, I guess?
        for(int nodeMesh = 0; nodeMesh < scene->mRootNode->mNumMeshes; ++nodeMesh)
        {
            SceneObject so{};
            so.meshId = scene->mRootNode->mMeshes[nodeMesh];
            aiMatrix4x4 t = scene->mRootNode->mTransformation;
            so.transform = glm::mat4x4(
                    t.a1, t.a2, t.a3, t.a4,
                    t.b1, t.b2, t.b3, t.b4,
                    t.c1, t.c2, t.c3, t.c4,
                    t.d1, t.d2, t.d3, t.d4
                    );
            gfxScene.addObject(std::move(so));
        }
    }
    else
    {
        Log(S_WARNING) << "Could not load " << filename << ", check paths?";
    }
    return gfxScene;
}
