#pragma once

#include <types/StdInc.hpp>



namespace Ruby::Memory {
    void* Malloc(size_t sz);
    
    void Free(void* ptr);
}