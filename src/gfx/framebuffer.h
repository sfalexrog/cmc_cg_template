#ifndef CMC_CG_TEMPLATE_FRAMEBUFFER_H
#define CMC_CG_TEMPLATE_FRAMEBUFFER_H

#include <glbinding/gl33core/gl.h>

namespace Gfx
{
    using namespace gl33core;

    class FramebufferBinding;

    class Framebuffer
    {
    private:
        GLuint id;


    public:

        Framebuffer(const Framebuffer& other) = delete;

        Framebuffer()
        {
            glGenFramebuffers(1, &id);
        }

        bool isComplete();

        Framebuffer& attachTexture(GLenum attachment, GLuint textureId, GLint level = 0);



        GLuint get() const
        {
            return id;
        }

        ~Framebuffer()
        {
            glDeleteFramebuffers(1, &id);

        }
    };

    class FramebufferBinding
    {
    private:
        GLint oldBinding;

    public:
        FramebufferBinding(const FramebufferBinding& other) = delete;

        explicit FramebufferBinding(const Framebuffer &fb)
        {
            glGetIntegerv(GL_FRAMEBUFFER_BINDING, &oldBinding);
            glBindFramebuffer(GL_FRAMEBUFFER, fb.get());
        }
        ~FramebufferBinding()
        {
            glBindFramebuffer(GL_FRAMEBUFFER, (GLuint)oldBinding);
        }
    };
}

#endif //CMC_CG_TEMPLATE_FRAMEBUFFER_H
