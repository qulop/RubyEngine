#pragma once

#include <types/TypeTraits.hpp>


namespace Ruby::Platform {
    void* virtualAlloc(size_t size);
    void virtualFree(void* address, size_t size);

    void* createMemoryMapping();
}