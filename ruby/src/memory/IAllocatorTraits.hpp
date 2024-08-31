#pragma once

#include <utility/Definitions.hpp>


namespace Ruby::Memory {
    interface IAllocatorTraits {
        virtual void* Allocate(size_t n) = 0;
        void* allocate(size_t n) {
            return Allocate(n);
        }

        virtual void Deallocate(void* ptr, size_t n) = 0;
        void deallocate(void* ptr, size_t n) {
            Deallocate(ptr, n);
        }
    };
}