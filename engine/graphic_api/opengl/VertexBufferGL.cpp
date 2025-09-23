#include "VertexBufferGL.hpp"

#include <glad/glad.h>


namespace Ruby::OpenGL {
    VertexBufferGL::VertexBufferGL(size_t size) {
        glGenBuffers(1, &m_id);
        glBindBuffer(GL_ARRAY_BUFFER, m_id);
        glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
    }


    VertexBufferGL::VertexBufferGL(float* vertices, size_t size) {
        glGenBuffers(1, &m_id);
        glBindBuffer(GL_ARRAY_BUFFER, m_id);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }


    void VertexBufferGL::Bind() const {
        glBindBuffer(GL_ARRAY_BUFFER, m_id);
    }


    void VertexBufferGL::Unbind() const {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }


    void VertexBufferGL::SetData(const void* data, size_t size) {
        Bind();
        glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
    }


    VertexBufferGL::~VertexBufferGL() {
        glDeleteBuffers(1, &m_id);
    }

}