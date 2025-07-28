#pragma once

#include <renderer/VertexArray.hpp>
#include <renderer/IndexBuffer.hpp>
#include <renderer/VertexBuffer.hpp>

#include "VertexBufferGL.hpp"
#include "IndexBufferGL.hpp"
#include "TypesGL.hpp"


namespace Ruby::OpenGL {
    class RUBY_API VertexArrayGL : public Ruby::VertexArray {
    public:
        VertexArrayGL();
        explicit VertexArrayGL(const VertexBuffer& vbo);

        void Bind() const override;
        void Unbind() const override;

        //void AddVBO(const VertexBuffer& vbo) override;
        void SetEBO(const IndexBuffer& ebo) override;

        RUBY_NODISCARD const Vector<VertexBuffer>& GetVBO() const override;
        RUBY_NODISCARD const IndexBuffer* GetEBO() const override;

        ~VertexArrayGL() override;

    private:
        GlID m_id = RUBY_GL_UNDEFINED_ID;

        Vector<VertexBufferGL> m_vertexBuffers;
        IndexBufferGL m_ebo;
    };
}