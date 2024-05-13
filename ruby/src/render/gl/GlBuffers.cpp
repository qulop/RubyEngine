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

    GlVertexBuffer::GlVertexBuffer(const std::span<float>& vertices)
    {
        glGenBuffers(1, &m_id);
        glBindBuffer(GL_ARRAY_BUFFER, m_id);
        glBufferData(GL_ARRAY_BUFFER, vertices.size_bytes(), vertices.data(), GL_STATIC_DRAW);
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

    void GlVertexBuffer::SetLayoutTypes(std::initializer_list<ShaderDataTypes> layout)
    { m_layout.Set(layout); }

    GlVertexBuffer::~GlVertexBuffer()
    { glDeleteBuffers(1, &m_id); }



    GlIndexBuffer::GlIndexBuffer(const std::span<u32>& indices)
    {
        glGenBuffers(1, &m_id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size_bytes(), indices.data(), GL_STATIC_DRAW);

        m_count = indices.size();
    }

    void GlIndexBuffer::Bind()
    { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id); }

    void GlIndexBuffer::Unbind()
    { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

    size_t GlIndexBuffer::GetCount() const
    { return m_count; }


    GlIndexBuffer::~GlIndexBuffer()
    { glDeleteBuffers(1, &m_id); }


}