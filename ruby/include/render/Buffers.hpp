#pragma once

#include <utility/Definitions.hpp>
#include "ShaderTypes.hpp"


namespace Ruby
{
    namespace Details::Render
    {
        struct VBOLayoutElement
        {
            VBOLayoutElement() = default;
            explicit VBOLayoutElement(ShaderTypes type, bool isNormalized = false) :
                type(type),
                count(getShaderTypeElementsCount(type)),
                countPerLine(getShaderTypeElementsCount(type, false)),
                size(getShaderTypeSize(type)),
                isNormalized(isNormalized)
            {}

            i32 count = 0;
            i32 countPerLine = 0;
            i32 size = 0;
            ShaderTypes type = ShaderTypes::NONE;
            bool isNormalized = false;
            size_t offset = 0;
        };


        class VBOLayout
        {
        public:
            using ElementType = VBOLayoutElement;

            VBOLayout() = default;

            void Set(std::initializer_list<ShaderTypes> types);

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


    abstract class VertexBuffer
    {
    public:
        using LayoutType = Details::Render::VBOLayout;

        virtual void Bind() = 0;
        virtual void Unbind() = 0;

        virtual void SetData(const void* data, size_t size) = 0;
        virtual void SetLayoutTypes(std::initializer_list<ShaderTypes> layout) = 0;
        virtual const LayoutType& GetLayout() const = 0;

        Ptr<VertexBuffer> Create(size_t size);
        Ptr<VertexBuffer> Create(const std::span<float>& vertices);

        virtual ~VertexBuffer() = default;
    };

    abstract class IndexBuffer
    {
    public:
        virtual void Bind() = 0;
        virtual void Unbind() = 0;

        virtual size_t GetCount() const = 0;

        static Ptr<IndexBuffer> Create(const std::span<i32>& indices);

        virtual ~IndexBuffer() = default;
    };
}