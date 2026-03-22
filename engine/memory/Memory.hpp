#pragma once

#include <common/PCH.hpp>



namespace Kiwi::Memory {
    void* Malloc(size_t sz);
    
    void Free(void* ptr);
}