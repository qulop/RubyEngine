#pragma once

#include <common/Definitions.hpp>
#include <common/Errors.hpp>
#include <common/types/Result.hpp>


namespace Kiwi::Memory::Details {
    constexpr size_t STACK_ALLOC_MAX = 1024 * 16;   // 16kb

    constexpr size_t ALLOC_DEFAULT_POOL_SIZE = 1024 * 4; // 4Kb
}


namespace Kiwi::Memory {
    struct AllocatedBlock {
        size_t size = 0;
        void* ptr = nullptr;

        AllocatedBlock() = default;
        AllocatedBlock(size_t sz, void* ptr) :
            size(sz),
            ptr(ptr)
        {}

        AllocatedBlock(const AllocatedBlock&) = default;
        AllocatedBlock& operator=(const AllocatedBlock&) = default;

        AllocatedBlock(AllocatedBlock&& other) noexcept :
            size(std::exchange(other.size, 0)),
            ptr(std::exchange(other.ptr, nullptr))
        {}

        AllocatedBlock& operator=(AllocatedBlock&& other) noexcept {
            size = std::exchange(other.size, 0);
            ptr = std::exchange(other.ptr, nullptr);

            return *this;
        }

        template<typename Tx>
        Tx* CastPtr() {
            return CastTo<Tx*>(ptr);
        }

        KIWI_NODISCARD bool IsAllocated() const {
            return ptr == nullptr;
        }
    };


    class AAllocatorTraits {
        KIWI_NODISCARD virtual Result<AllocatedBlock> Allocate(size_t n) = 0;
        KIWI_NODISCARD void* allocate(size_t n) {
            auto res = Allocate(n);

            return res ? res->ptr : nullptr;
        }

        KIWI_NODISCARD virtual void Deallocate(AllocatedBlock block) = 0;
        KIWI_NODISCARD void deallocate(void* ptr, size_t n) {
            Deallocate(AllocatedBlock{ n, ptr });
        }

        virtual ~AAllocatorTraits() = default;
    };
}