#include "IndexBufferGL.hpp"

#include <glad/glad.h>


namespace Ruby::OpenGL {
    IndexBufferGL::IndexBufferGL(float* indices, size_t size) {
        SetData(indices, size);
    }


    void IndexBufferGL::Bind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
    }


    void IndexBufferGL::Unbind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }


    void IndexBufferGL::SetData(Ruby::f32* indices, size_t size) {
        glGenBuffers(1, &m_id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);

        m_count = size;
    }


    size_t IndexBufferGL::GetCount() const {
        return m_count;
    }


    IndexBufferGL::~IndexBufferGL() {
        glDeleteBuffers(1, &m_id);
    }
}