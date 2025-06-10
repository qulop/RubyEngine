#include "Memory.hpp"

#include <types/TypeTraits.hpp>


namespace Ruby::Memory {
    struct BlockHeader {
        
    };


    void* malloc(size_t sz) {

    }


    void free(void* ptr) {
        auto* header = (BlockHeader*)((byte*)(ptr) - sizeof(BlockHeader)); 
    }
}