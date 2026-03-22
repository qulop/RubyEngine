#include "Memory.hpp"

#include <common/TypeTraits.hpp>


namespace Kiwi::Memory {
    void* Malloc(size_t sz) {
        return std::malloc(sz);
    }

    void Free(void* ptr) {
        std::free(ptr);
    }
}