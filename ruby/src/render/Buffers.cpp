#include <render/Buffers.hpp>
#include <render/gl/GlBuffers.hpp>

namespace Ruby
{
    void Details::Render::VBOLayout::Set(std::initializer_list<ShaderTypes> types)
    {
        for (auto i : types)
            m_elements.emplace_back(i, false);
        CalculateStrideAndOffset();
    }

    void Details::Render::VBOLayout::CalculateStrideAndOffset()
    {
        i32 offset = 0;
        for (auto& element : m_elements)
        {
            element.offset = offset;

            offset += element.size;
            m_stride += element.size;
        }
    }



    /// TODO: ADD CHECK ON USED API
    Ptr<VertexBuffer> VertexBuffer::Create(size_t size)
    {
        return std::make_shared<GlVertexBuffer>(size);
    }

    /// TODO: ADD CHECK ON USED API
    Ptr<VertexBuffer> VertexBuffer::Create(const std::span<float>& vertices)
    {
        return std::make_shared<GlVertexBuffer>(vertices);
    }

    /// TODO: ADD CHECK ON USED API
    Ptr<IndexBuffer> IndexBuffer::Create(const std::span<i32>& indices)
    {
        return std::make_shared<GlIndexBuffer>(indices);
    }
}