#include "VertexBufferGL.hpp"

#include <utility/Assert.hpp>

#include <glad/glad.h>


namespace Ruby::OpenGL {
    VertexBufferGL::VertexBufferGL() {
        glGenBuffers(1, &m_id);
    }

    VertexBufferGL::VertexBufferGL(EBufferType type)
    {
        glGenBuffers(1, &m_id);
    }

    void VertexBufferGL::SetData(const void* data, size_t size) {
        RUBY_ASSERT_BASIC(IsValidResourceID(m_id));
        RUBY_ASSERT(data && size > 0, "Data pointer and size should be valid!");

        GLenum drawType = m_bufferType == EBufferType::STATIC_BUFFER ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW;

        glBindBuffer(GL_ARRAY_BUFFER, m_id);
        glBufferData(GL_ARRAY_BUFFER, size, data, drawType);
    }

    void VertexBufferGL::InitEmptyBuffer(EBufferType bufferType) {
        RUBY_ASSERT_BASIC(m_id != RUBY_GL_UNDEFINED_BUFFER);

        Super::InitEmptyBuffer(bufferType);
        glGenBuffers(1, &m_id);
    }

    void VertexBufferGL::ReleaseObject() {
        glDeleteBuffers(1, &m_id);
        m_id = RUBY_GL_UNDEFINED_BUFFER;
    }


    VertexBufferGL::~VertexBufferGL() {
        glDeleteBuffers(1, &m_id);
    }

}