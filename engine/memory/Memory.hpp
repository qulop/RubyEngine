#pragma once

#include <types/StdInc.hpp>



namespace Ruby::Memory {
    void* malloc(size_t sz);
    
    void free(void* ptr);
}