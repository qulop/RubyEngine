#pragma once

#include <glad/glad.h>

#include <renderer/buffers/ObjectGPU.hpp>


#define KIWI_GL_UNDEFINED_ID (0)
#define KIWI_GL_UNDEFINED_BUFFER (0)

namespace Kiwi::OpenGL {
    using GlBuffer = GLuint;
    using GlID = GLuint;


    KIWI_NODISCARD inline bool IsValidResourceID(GLuint id) {
        return id != KIWI_GL_UNDEFINED_ID;
    }
}