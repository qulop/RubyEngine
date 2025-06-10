#include "Win32Utils.hpp"

#include <platform/general_api/Memory.hpp>

#ifdef _DEBUG
    #define HEAP_ALLOC_FLAGS HEAP_GENERATE_EXCEPTIONS | HEAP_ZERO_MEMORY
#else
    #define HEAP_ALLOC_FLAGS HEAP_ZERO_MEMORY
#endif


namespace Ruby::Platform {
    void* virtualAlloc(size_t size) {
        HANDLE heap = GetProcessHeap();
        if (heap == static_cast<HANDLE>(NULL)) {
            return nullptr;
        }

        return HeapAlloc(heap, HEAP_ALLOC_FLAGS, size);
    }

    void virtualFree(void* address, size_t size) {
        HANDLE heap = GetProcessHeap();
        if (heap == static_cast<HANDLE>(NULL)) {
            return;
        }

        HeapFree(heap, NULL, address);
    }
}