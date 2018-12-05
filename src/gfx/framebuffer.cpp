#include "framebuffer.h"

namespace Gfx
{
    bool Framebuffer::isComplete()
    {
        FramebufferBinding fb(*this);
        return glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
    }

    Framebuffer& Framebuffer::attachTexture(gl::GLenum attachment, gl::GLuint textureId, gl::GLint level)
    {
        FramebufferBinding fb(*this);
        glFramebufferTexture(GL_FRAMEBUFFER, attachment, textureId, level);
        return *this;
    }
}

