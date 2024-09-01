#pragma once

#include <utility/Definitions.hpp>


namespace Ruby::Memory {
    namespace Details {
        constexpr size_t ALLOC_DEFAULT_POOL_SIZE = 1024 * 64; // 64Kb
    };


    struct AllocatedBlock {
        const size_t size = 0;
        void* ptr = nullptr;

        AllocatedBlock() = default;
        AllocatedBlock(size_t s, void* p) :
            size(s),
            ptr(p)
        {}
    };


    interface IAllocatorTraits {
        virtual AllocatedBlock Allocate(size_t n) = 0;

        void* allocate(size_t n) {
            return Allocate(n).ptr;
        }

        virtual void Deallocate(AllocatedBlock block) = 0;

        void deallocate(void* ptr, size_t n) {
            Deallocate(AllocatedBlock{ n, ptr });
        }
    };
}