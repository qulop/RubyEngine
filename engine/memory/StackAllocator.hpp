#pragma once

#include "AllocatorTraits.hpp"

#include <types/TypeTraits.hpp>
#include <types/Errors.hpp>
#include <utility/Assert.hpp>


namespace Kiwi::Memory {
    template<size_t size = Details::ALLOC_DEFAULT_POOL_SIZE>
        requires (size <= Details::STACK_ALLOC_MAX)
    class StackAllocator : public AAllocatorTraits {
    public:
        StackAllocator() {  // NOLINT
            std::fill(std::begin(m_memory), std::end(m_memory), 0);
        }

        KIWI_NODISCARD Expected<AllocatedBlock, Error<EGeneralError>> Allocate(size_t s) override {
            if ((m_current + s) > (m_memory + size)) {
                return Unexpected(
                    Error<EGeneralError>::FromKind(EGeneralError::OUT_OF_MEMORY)
                );
            }

            void* ret = m_current;
            m_current += s;

            return AllocatedBlock(s, ret);
        }

        void Deallocate(AllocatedBlock block) override {
            KIWI_ASSERT(IsOwns(block),
                    "Transmitted memory block({}) doesn't belong to this allocator(with borders from {} to {}",
                        block.ptr, (void*)m_memory, (void*)(m_memory + size));
            KIWI_ASSERT((block.ptr == m_current - block.size),
                    "In StackAllocator you can deallocate only last allocated memory");

            m_current -= block.size;
        }

        KIWI_NODISCARD size_t GetSize() const {
            return size;
        }

        bool IsOwns(AllocatedBlock block) {
            auto* ptr = block.GetPtr<byte>();

            return (ptr >= m_memory) && (ptr <= m_memory + size);
        }

    private:
        alignas(std::max_align_t) byte m_memory[size];
        byte* m_current = m_memory;
    };
}