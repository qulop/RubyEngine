#include <render/gl/GlVertexArray.hpp>
#include <glad/glad.h>


namespace Ruby
{
    static GLenum toGLShaderType(ShaderTypes type)
    {
        switch (type)
        {
            case ShaderTypes::FLOAT:
            case ShaderTypes::VEC2:
            case ShaderTypes::VEC3:
            case ShaderTypes::VEC4:
            case ShaderTypes::MAT3:
            case ShaderTypes::MAT4:
                return GL_FLOAT;

            case ShaderTypes::INT:
            case ShaderTypes::IVEC2:
            case ShaderTypes::IVEC3:
            case ShaderTypes::IVEC4:
                return GL_INT;

            case ShaderTypes::BOOL:
                return GL_BOOL;

            default:
                RUBY_WRECK("toGLShaderType() : Unknown shader type!");
        }
    }


    GlVertexArray::GlVertexArray()
    { glGenVertexArrays(1, &m_id); }

    void GlVertexArray::Bind()
    { glBindVertexArray(m_id); }

    void GlVertexArray::Unbind()
    { glBindVertexArray(0); }

    void GlVertexArray::SetVBO(const Ptr<VertexBuffer>& vbo)
    {
        auto& layout = vbo->GetLayout();

        this->Bind();
        vbo->Bind();

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
                RUBY_WRECK("GlVertexArray::SetVBO() : Unknown shader type!");
        }
    }

    GlVertexArray::~GlVertexArray()
    { glDeleteVertexArrays(1, &m_id); }
}
