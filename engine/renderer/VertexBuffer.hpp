#pragma once

#include <utility/Definitions.hpp>

#include <renderer/shaders/ShaderMetaInfo.hpp>


namespace Ruby {
  /*  namespace Details::Renderer {
        struct _VBOLayoutElement {
            _VBOLayoutElement() = default;
            explicit _VBOLayoutElement(ShaderDataTypes type, bool isNormalized = false) :
                type(type),
                count(ShaderMetaInfo::GetShaderTypeElementsCount(type)),
                countPerLine(getShaderTypeElementsCount(type, false)),
                size(getShaderDataTypeSize(type)),
                isNormalized(isNormalized) {}

            i32 count = 0;
            i32 countPerLine = 0;
            i32 size = 0;
            ShaderDataTypes type = ShaderDataTypes::NONE;
            bool isNormalized = false;
            size_t offset = 0;
        };


        class _VBOLayout {
        public:
            using ElementType = _VBOLayoutElement;

            _VBOLayout() = default;

            void Set(std::initializer_list<ShaderDataTypes> types);

            RUBY_NODISCARD i32 GetStride() const {
                return m_stride;
            }

            RUBY_NODISCARD const Vector<ElementType>& GetElements() const {
                return m_elements;
            }

        private:
            void CalculateStrideAndOffset();

        private:
            Vector<ElementType> m_elements;
            i32 m_stride = 0;
        };
    }*/


    class RUBY_API VertexBuffer {
    public:
        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void SetData(const void* data, size_t size) = 0;
        //void SetLayoutTypes(std::initializer_list<ShaderDataTypes> layout);
        //RUBY_NODISCARD const LayoutType& GetLayout() const;

        virtual ~VertexBuffer() = default;
    };
}