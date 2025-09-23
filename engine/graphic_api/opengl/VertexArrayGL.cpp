#include "VertexArrayGL.hpp"

#include <types/Logger.hpp>
#include <renderer/shaders/ShaderMetaInfo.hpp>

#include <glad/glad.h>


namespace {
    GLenum toGLShaderType(Ruby::ShaderDataTypes type) {
        using Ruby::ShaderDataTypes;

        switch (type) {
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
                RUBY_CRITICAL("toGLShaderType() : Unknown shader type!");
                return 0;
        }
    }
}


namespace Ruby::OpenGL {
    VertexArrayGL::VertexArrayGL() {
        glGenVertexArrays(1, &m_id);
    }


    VertexArrayGL::VertexArrayGL(const VertexBuffer& vbo) {
        /*AddVBO(vbo);*/
    }


    void VertexArrayGL::Bind() const {
        glBindVertexArray(m_id);
    }


    void VertexArrayGL::Unbind() const {
        glBindVertexArray(0);
    }


    //void VertexArrayGL::AddVBO(const VertexBuffer& vbo) {
    //    auto& layout = vbo.GetLayout();

    //    Bind();
    //    vbo.Bind();

    //    int index = 0;
    //    for (const auto& elem : layout.GetElements()) {
    //        auto normalized = (elem.isNormalized) ? GL_TRUE : GL_FALSE;
    //        auto glShaderType = toGLShaderType(elem.type);

    //        if (isIntShaderType(elem.type)) {
    //            glVertexAttribIPointer(index,
    //                                   elem.count,
    //                                   glShaderType,
    //                                   layout.GetStride(),
    //                                   (void*)elem.offset);
    //            glEnableVertexAttribArray(index);
    //            ++index;
    //        }

    //        else if (isFloatShaderType(elem.type)) {
    //            glVertexAttribPointer(index,
    //                                  elem.count,
    //                                  glShaderType,
    //                                  normalized,
    //                                  layout.GetStride(),
    //                                  (void*)elem.offset);
    //            glEnableVertexAttribArray(index);
    //            ++index;
    //        }

    //        else if (isMatrixShaderType(elem.type)) {
    //            for (size_t i = 0; i < elem.countPerLine; i++, index++) {
    //                size_t offset = elem.offset + (elem.countPerLine * sizeof(float) * i);
    //                glVertexAttribPointer(
    //                        index,
    //                        elem.countPerLine,
    //                        glShaderType,
    //                        normalized,
    //                        layout.GetStride(),
    //                        (void*)(offset));
    //                glEnableVertexAttribArray(index);
    //            }
    //        }

    //        else {
    //            RUBY_CRITICAL("VertexArrayGL::SetVBO() : Unknown shader type!");
    //        }
    //    }


void VertexArrayGL::SetEBO(const IndexBuffer& ebo) {
    Bind();
    ebo.Bind();

    //m_ebo = ebo;
}


const Vector<VertexBuffer>& VertexArrayGL::GetVBO() const {
    return {};
}


const IndexBuffer* VertexArrayGL::GetEBO() const {
    return &m_ebo;
}


VertexArrayGL::~VertexArrayGL() {
    glDeleteVertexArrays(1, &m_id);
}
}