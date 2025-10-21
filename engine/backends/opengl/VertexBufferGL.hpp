#pragma once

#include <renderer/VertexBuffer.hpp>
#include <utility/Definitions.hpp>

#include "TypesGL.hpp"


namespace Ruby::OpenGL {
    class RUBY_API VertexBufferGL : public Ruby::VertexBuffer {
    public:
        VertexBufferGL() = default;
        explicit VertexBufferGL(size_t size);
        VertexBufferGL(f32* vertices, size_t size);

        void Bind() const override;
        void Unbind() const override;

        void SetData(const void* data, size_t size) override;

        ~VertexBufferGL() override;

    private:
        GlID m_id = RUBY_GL_UNDEFINED_ID;
    };
}