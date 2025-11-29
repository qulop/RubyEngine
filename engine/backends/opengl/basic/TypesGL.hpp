#pragma once

#include <glad/glad.h>

#include <renderer/buffers/ObjectGPU.hpp>


#define RUBY_GL_UNDEFINED_ID (0)
#define RUBY_GL_UNDEFINED_BUFFER (0)

namespace Ruby::OpenGL {
    using GlBuffer = GLuint;
    using GlID = GLuint;


    RUBY_NODISCARD inline bool IsValidResourceID(GLuint id) {
        return id != RUBY_GL_UNDEFINED_ID;
    }
}