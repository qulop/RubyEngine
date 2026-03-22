#pragma once

#include <common/StdInc.hpp>



namespace Kiwi::Memory {
    void* Malloc(size_t sz);
    
    void Free(void* ptr);
}