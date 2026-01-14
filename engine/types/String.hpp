#pragma once

#include <types/TypeTraits.hpp>
#include <types/Concepts.hpp>
#include <types/CString.hpp>
#include <types/Array.hpp>

#include <memory/AllocatorBase.hpp>


namespace Kiwi::StringUtils {
    template<std::ranges::input_range Tx>
        requires Concepts::ConvertibleTo<std::ranges::range_value_t<Tx>, String>
    String Join(const Tx& rng, char sep = ' ') {
        return std::accumulate(
            std::next(rng.begin()), rng.end(), String{ rng.front() },
            [&](String&& acc, const auto& s) {
                return acc + sep + s;
            }
        );
    }

    constexpr String EmptyString() {
        return String{};
    }
}

namespace Kiwi {
    template<Concepts::TrivialCharacter T, typename A = Memory::AllocatorBase<T>>
    class BasicString : DynArray<T, A> {
    public:
        using Super = DynArray<T, A>;
        using SelfType = BasicString;

        using ValueType = T;
        using value_type = ValueType;

        using ReferenceType = ValueType&;
        using reference = ReferenceType;

        using PointerType = ValueType*;
        using pointer = PointerType;

        using ConstPointerType = const ValueType*;
        using const_pointer = ConstPointerType;

        using AllocatorType = A;
        using allocator_type = AllocatorType;

    public:
        static constexpr float CAPACITY_COEFFICIENT = 1.5f;
        static constexpr size_t INITIAL_CAPACITY = 20;

    public:
        static SelfType New() {
            SelfType r;
            r.Resize(INITIAL_CAPACITY);
        }

        static SelfType New(PointerType ptr, size_t sz) {
            SelfType self;
        }


        template<std::ranges::input_range TInputRange>
            requires Concepts::ConvertibleTo<std::ranges::range_value_t<TInputRange>, SelfType>
        static SelfType Join(const TInputRange& rng, char sep = ' ') {
            return std::accumulate(
                std::next(rng.begin()), rng.end(), SelfType{ rng.front() },
                [&](SelfType&& acc, const auto& s) {
                    return acc + sep + s;
                }
            );
        }

        static SelfType EmptyString() {
            return SelfType{};
        }

    public:
        BasicString(PointerType ptr, size_t sz) {

        }


    public:
        KIWI_NODISCARD bool IsEmpty() const {
            KIWI_ASSERT_BASIC(m_str.IsAllocated());

            return m_str.size == 0;
        }

        KIWI_NODISCARD size_t Size() const {
            return m_str.size;
        }

        KIWI_NODISCARD size_t Capacity() const {
            return m_capacity;
        }

        KIWI_NODISCARD PointerType Data() {
            return m_str.GetPtr<ValueType>();
        }

        KIWI_NODISCARD ConstPointerType Data() const {
            return m_str.GetPtr<ValueType>();
        }

        KIWI_NODISCARD PointerType CString() {
            return Data();
        }

        KIWI_NODISCARD ConstPointerType CString() const {
            return Data();
        }

        KIWI_NODISCARD ValueType At(size_t idx) const {
            KIWI_ASSERT_BASIC(m_str.IsAllocated() && idx < m_str.size);

            return Data()[idx];
        }

        KIWI_NODISCARD bool Resize(size_t sz) {
            if (!m_str.IsAllocated()) {
                m_str = m_allocator.Allocate(sz);
                return m_str.IsAllocated();
            }


            return true;
        }

        KIWI_NODISCARD bool ResizeWithChar(ValueType ch, size_t sz) {
            if (!m_str.IsAllocated()) {
                m_str = m_allocator.Allocate(sz);
                return m_str.IsAllocated();
            }


            return true;
        }

    private:
        Memory::AllocatedBlock m_str;
        size_t m_capacity = 0;

        AllocatorType m_allocator;

    };
}