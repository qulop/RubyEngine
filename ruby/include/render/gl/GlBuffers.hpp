#pragma once

#include <render/Buffers.hpp>


namespace Ruby
{
    class GlVertexBuffer : public VertexBuffer
    {
    public:
        explicit GlVertexBuffer(size_t size);
        GlVertexBuffer(const std::span<float>& vertices);

        void Bind() override;
        void Unbind() override;

        void SetData(const void* data, size_t size) override;
        void SetLayoutTypes(std::initializer_list<ShaderDataTypes> layout) override;

        RUBY_NODISCARD const LayoutType& GetLayout() const override
        { return m_layout; }


        virtual ~GlVertexBuffer();

    private:
        u32 m_id = std::numeric_limits<u32>::max();
        LayoutType m_layout;
    };


    class GlIndexBuffer : public IndexBuffer
    {
    public:
        GlIndexBuffer(const std::span<u32>& indices);

        void Bind() override;
        void Unbind() override;

        RUBY_NODISCARD size_t GetCount() const override;


        virtual ~GlIndexBuffer();

    private:
        u32 m_id = std::numeric_limits<u32>::max();
        size_t m_count = 0;
    };
}