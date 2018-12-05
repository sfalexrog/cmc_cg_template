#ifndef CMC_CG_TEMPLATE_SHADER_H
#define CMC_CG_TEMPLATE_SHADER_H

#include <glbinding/gl33core/gl.h>

#include "util/logger.h"

namespace Gfx
{
    using namespace gl33core;

    class Shader
    {
    public:
        GLuint program;
    public:
        Shader(const Shader& other) = delete;


        Shader()
        {
            program = glCreateProgram();
        }

        Shader& addStage(GLenum stage, const char* source)
        {
            auto shader = glCreateShader(stage);
            glShaderSource(shader, 1, &source, nullptr);
            glCompileShader(shader);
            GLboolean status;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
            if (status != GL_TRUE)
            {
                GLint logLength;
                glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
                char *log = new char[logLength + 1];
                glGetShaderInfoLog(shader, logLength + 1, nullptr, log);
                log[logLength] = '\0';
                Log(S_WARNING) << "Shader compilation failed! Info log: " << log;
                delete[] log;
            }
            else
            {
                glAttachShader(program, shader);
            }
            glDeleteShader(shader);
            return *this;
        }

        Shader& addStage(const char* filename);
        Shader& addStage(const char* filename, GLenum stage);

        Shader& link()
        {
            glLinkProgram(program);
            GLboolean status;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &status);
            if (status != GL_TRUE)
            {
                GLint logLength;
                glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
                char *log = new char[logLength + 1];
                glGetProgramInfoLog(program, logLength + 1, nullptr, log);
                Log(S_WARNING) << "Program linkage failed! Info log: " << log;
            }
            return *this;
        }

        ~Shader()
        {
            glDeleteProgram(program);
        }
    };
}

#endif //CMC_CG_TEMPLATE_SHADER_H
