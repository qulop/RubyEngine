#pragma once

#include <utility/Definitions.hpp>
#include "ShaderDataTypes.hpp"


namespace Ruby
{
    namespace Details::Renderer
    {
        struct VBOLayoutElement
        {
            VBOLayoutElement() = default;
            explicit VBOLayoutElement(ShaderDataTypes type, bool isNormalized = false) :
                type(type),
                count(getShaderTypeElementsCount(type)),
                countPerLine(getShaderTypeElementsCount(type, false)),
                size(getShaderDataTypeSize(type)),
                isNormalized(isNormalized)
            {}

            i32 count = 0;
            i32 countPerLine = 0;
            i32 size = 0;
            ShaderDataTypes type = ShaderDataTypes::NONE;
            bool isNormalized = false;
            size_t offset = 0;
        };


        class VBOLayout
        {
        public:
            using ElementType = VBOLayoutElement;

            VBOLayout() = default;

            void Set(std::initializer_list<ShaderDataTypes> types);

            RUBY_NODISCARD i32 GetStride() const
            { return m_stride; }

            RUBY_NODISCARD const RubyVector<ElementType>& GetElements() const
            { return m_elements; }

        private:
            void CalculateStrideAndOffset();

        private:
            RubyVector<ElementType> m_elements;
            i32 m_stride = 0;
        };
    }


    class VertexBuffer
    {
    public:
        using LayoutType = Details::Renderer::VBOLayout;

        explicit VertexBuffer(size_t size);
        VertexBuffer(float* vertices, size_t size);

        void Bind() const;
        void Unbind() const;

        void SetData(const void* data, size_t size);
        void SetLayoutTypes(std::initializer_list<ShaderDataTypes> layout);
        RUBY_NODISCARD const LayoutType& GetLayout() const;

        ~VertexBuffer();

    private:
        u32 m_id = std::numeric_limits<u32>::max();
        LayoutType m_layout;
    };

    class IndexBuffer
    {
    public:
        IndexBuffer(float* indices, size_t size);

        void Bind() const;
        void Unbind() const;

        RUBY_NODISCARD size_t GetCount() const;

        ~IndexBuffer();

    private:
        u32 m_id = std::numeric_limits<u32>::max();
        size_t m_count = 0;
    };
}