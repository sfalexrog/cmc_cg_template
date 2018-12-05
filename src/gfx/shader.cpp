#include "shader.h"

#include <iostream>
#include <fstream>

namespace Gfx
{
    Shader& Shader::addStage(const char *filename)
    {
        // Use the whole OpenGL namespace since some enums are not available in 3.3
        using namespace gl;

        std::string fname(filename);
        std::string extension = fname.substr(fname.size() - 4);
        GLenum stage = GL_NONE;
        if (extension == "vert")
        {
            stage = GL_VERTEX_SHADER;
        }
        else if (extension == "frag")
        {
            stage = GL_FRAGMENT_SHADER;
        }
        else if (extension == "geom")
        {
            stage = GL_GEOMETRY_SHADER;
        }
        else if (extension == "tese")
        {
            // NOTE: Not in GL3.3
            stage = GL_TESS_EVALUATION_SHADER;
        }
        else if (extension == "tesc")
        {
            // NOTE: Not in GL3.3
            stage = GL_TESS_CONTROL_SHADER;
        }
        else if (extension == "comp")
        {
            stage = GL_COMPUTE_SHADER;
        }
        return addStage(filename, stage);
    }

    Shader& Shader::addStage(const char *filename, GLenum stage)
    {
        std::stringstream source;
        std::string line;
        std::ifstream src(filename);
        while(std::getline(src, line))
        {
            source << line << "\n";
        }
        return addStage(stage, source.str().c_str());
    }
}
