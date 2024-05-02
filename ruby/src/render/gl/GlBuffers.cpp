#pragma once

#include <render/gl/GlBuffers.hpp>
#include <glad/glad.h>


namespace Ruby
{
    GlVertexBuffer::GlVertexBuffer(size_t size)
    {
        glGenBuffers(1, &m_id);
        glBindBuffer(GL_ARRAY_BUFFER, m_id);
        glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
    }

    GlVertexBuffer::GlVertexBuffer(float* vertices, size_t size)
    {
        glGenBuffers(1, &m_id);
        glBindBuffer(GL_ARRAY_BUFFER, m_id);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }

    void GlVertexBuffer::Bind()
    { glBindBuffer(GL_ARRAY_BUFFER, m_id); }

    void GlVertexBuffer::Unbind()
    { glBindBuffer(GL_ARRAY_BUFFER, 0); }

    void GlVertexBuffer::SetData(const void* data, size_t size)
    {
        Bind();
        glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
    }
}