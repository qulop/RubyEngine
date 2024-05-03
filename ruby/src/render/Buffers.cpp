#include <render/Buffers.hpp>
#include <render/gl/GlBuffers.hpp>

namespace Ruby
{
    i32 Details::Render::VBOLayoutElement::GetTypeSize(ShaderTypes shType) const
    {
        switch(shType)
        {
            case ShaderTypes::FLOAT:
            case ShaderTypes::INT: return 4;

            case ShaderTypes::VEC2:
            case ShaderTypes::IVEC2: return 4 * 2;

            case ShaderTypes::VEC3:
            case ShaderTypes::IVEC3: return 4 * 3;

            case ShaderTypes::VEC4:
            case ShaderTypes::IVEC4: return 4 * 4;

            case ShaderTypes::BOOL: return 1;

            case ShaderTypes::MAT3: return 4 * 3 * 3;
            case ShaderTypes::MAT4: return 4 * 4 * 4;

            default:
                RUBY_ERROR("Details::Render::VBOLayoutElement::GetTypeSize() : Unknown shader type!");
        }
    }

    i32 Details::Render::VBOLayoutElement::GetElementsCount(ShaderTypes shType) const
    {
        switch(shType)
        {
            case ShaderTypes::INT:
            case ShaderTypes::FLOAT:
            case ShaderTypes::BOOL:
                return 1;

            case ShaderTypes::VEC2:
            case ShaderTypes::IVEC2:
                return 2;

            case ShaderTypes::VEC3:
            case ShaderTypes::IVEC3:
                return 3;

            case ShaderTypes::VEC4:
            case ShaderTypes::IVEC4:
                return 4;

            case ShaderTypes::MAT3: return 3 * 3;
            case ShaderTypes::MAT4: return 4 * 4;

            default:
                RUBY_ERROR("Details::Render::VBOLayoutElement::GetCount() : Unknown shader type!");
        }
    }

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