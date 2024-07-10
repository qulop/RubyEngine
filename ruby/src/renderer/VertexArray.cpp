#include "VertexArray.hpp"
#include <glad/glad.h>

namespace Ruby
{
    static GLenum toGLShaderType(ShaderDataTypes type)
    {
        switch (type)
        {
            case ShaderDataTypes::FLOAT:
            case ShaderDataTypes::VEC2:
            case ShaderDataTypes::VEC3:
            case ShaderDataTypes::VEC4:
            case ShaderDataTypes::MAT3:
            case ShaderDataTypes::MAT4:
                return GL_FLOAT;

            case ShaderDataTypes::INT:
            case ShaderDataTypes::IVEC2:
            case ShaderDataTypes::IVEC3:
            case ShaderDataTypes::IVEC4:
                return GL_INT;

            case ShaderDataTypes::BOOL:
                return GL_BOOL;

            default:
                RUBY_WRECK("toGLShaderType() : Unknown shader type!");
        }
    }


    VertexArray::VertexArray()
    { glGenVertexArrays(1, &m_id); }


    void VertexArray::Bind() const
    { glBindVertexArray(m_id); }


    void VertexArray::Unbind() const
    { glBindVertexArray(0); }


    void VertexArray::SetVBO(const VertexBuffer& vbo)
    {
        auto& layout = vbo.GetLayout();

        this->Bind();
        vbo.Bind();

        int index = 0;
        for (const auto& elem : layout.GetElements())
        {
            auto normalized = (elem.isNormalized) ? GL_TRUE : GL_FALSE;
            auto glShaderType = toGLShaderType(elem.type);

            if (isIntShaderType(elem.type))
            {
                glVertexAttribIPointer(index,
                                       elem.count,
                                       glShaderType,
                                       layout.GetStride(),
                                       (void*)elem.offset);
                glEnableVertexAttribArray(index);
                ++index;
            }

            else if (isFloatShaderType(elem.type))
            {
                glVertexAttribPointer(index,
                                      elem.count,
                                      glShaderType,
                                      normalized,
                                      layout.GetStride(),
                                      (void*)elem.offset);
                glEnableVertexAttribArray(index);
                ++index;
            }

            else if (isMatrixShaderType(elem.type))
            {
                for (size_t i = 0; i < elem.countPerLine; i++, index++)
                {
                    size_t offset = elem.offset + (elem.countPerLine * sizeof(float) * i);
                    glVertexAttribPointer(
                            index,
                            elem.countPerLine,
                            glShaderType,
                            normalized,
                            layout.GetStride(),
                            (void*)(offset));
                    glEnableVertexAttribArray(index);
                }
            }

            else
                RUBY_WRECK("VertexArray::SetVBO() : Unknown shader type!");
        }
    }


    VertexArray::~VertexArray()
    { glDeleteVertexArrays(1, &m_id); }
}