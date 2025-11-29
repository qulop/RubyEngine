#include "Memory.hpp"

#include <types/TypeTraits.hpp>


namespace Ruby::Memory {
    void* Malloc(size_t sz) {
        return std::malloc(sz);
    }

    void Free(void* ptr) {
        std::free(ptr);
    }
}