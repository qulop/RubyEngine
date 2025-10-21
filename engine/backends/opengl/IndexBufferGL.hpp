#pragma once

#include <renderer/IndexBuffer.hpp>
#include <types/TypeTraits.hpp>
#include <utility/Definitions.hpp>

#include "TypesGL.hpp"


namespace Ruby::OpenGL {
    class RUBY_API IndexBufferGL : public Ruby::IndexBuffer {
    public:
        IndexBufferGL() = default;
        IndexBufferGL(f32* indices, size_t size);

        void Bind() const override;
        void Unbind() const override;

        void SetData(f32* indices, size_t size) override;

        RUBY_NODISCARD size_t GetCount() const override;

        ~IndexBufferGL() override;

    private:
        GlID m_id = RUBY_GL_UNDEFINED_ID;
        size_t m_count = 0;
    };
}