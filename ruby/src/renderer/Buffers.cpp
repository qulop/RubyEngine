#pragma once

#include "Buffers.hpp"
#include <glad/glad.h>

namespace Ruby {
    void Details::Renderer::_VBOLayout::Set(std::initializer_list<ShaderDataTypes> types) {
        for (auto i : types)
            m_elements.emplace_back(i, false);
        CalculateStrideAndOffset();
    }

    void Details::Renderer::_VBOLayout::CalculateStrideAndOffset() {
        i32 offset = 0;
        for (auto& element : m_elements)
        {
            element.offset = offset;

            offset += element.size;
            m_stride += element.size;
        }
    }
    
    
    
    VertexBuffer::VertexBuffer(size_t size) {
        glGenBuffers(1, &m_id);
        glBindBuffer(GL_ARRAY_BUFFER, m_id);
        glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
    }


    VertexBuffer::VertexBuffer(float* vertices, size_t size) {
        glGenBuffers(1, &m_id);
        glBindBuffer(GL_ARRAY_BUFFER, m_id);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }


    void VertexBuffer::Bind() const {
        glBindBuffer(GL_ARRAY_BUFFER, m_id);
    }


    void VertexBuffer::Unbind() const {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }


    void VertexBuffer::SetData(const void* data, size_t size) {
        Bind();
        glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
    }


    void VertexBuffer::SetLayoutTypes(std::initializer_list<ShaderDataTypes> layout) {
        m_layout.Set(layout);
    }


    const VertexBuffer::LayoutType& VertexBuffer::GetLayout() const {
        return m_layout;
    }


    VertexBuffer::~VertexBuffer() {
        glDeleteBuffers(1, &m_id);
    }





    IndexBuffer::IndexBuffer(float* indices, size_t size) {
        SetData(indices, size);
    }


    void IndexBuffer::Bind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
    }


    void IndexBuffer::Unbind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }


    void IndexBuffer::SetData(Ruby::f32* indices, size_t size) {
        glGenBuffers(1, &m_id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);

        m_count = size;
    }


    size_t IndexBuffer::GetCount() const {
        return m_count;
    }


    IndexBuffer::~IndexBuffer() {
        glDeleteBuffers(1, &m_id);
    }
}