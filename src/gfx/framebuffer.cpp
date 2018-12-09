#include "framebuffer.h"

namespace Gfx
{
    bool Framebuffer::isComplete()
    {
        FramebufferBinding fb(*this);
        return glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
    }

    Framebuffer& Framebuffer::attachRenderbuffer(gl::GLenum attachment)
    {
        FramebufferBinding fb(*this);
        GLuint rb;
        glGenRenderbuffers(1, &rb);
        ownedRenderbuffers.push_back(rb);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, attachment, GL_RENDERBUFFER, rb);
        return *this;
    }

    Framebuffer& Framebuffer::attachTexture(gl::GLenum attachment, gl::GLuint textureId, gl::GLint level)
    {
        FramebufferBinding fb(*this);
        glFramebufferTexture(GL_FRAMEBUFFER, attachment, textureId, level);
        return *this;
    }
}

