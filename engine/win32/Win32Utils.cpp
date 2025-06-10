#include "Win32Utils.hpp"

#include <types/Logger.hpp>


namespace Ruby::Platform::Win32 {
    HANDLE getStdHandle(DWORD stdHnd, bool abortOnError) {
        HANDLE handle = GetStdHandle(stdHnd);
        if (handle != NULL && handle != INVALID_HANDLE_VALUE) {
            return handle;
        }

        if (!abortOnError) {
            return INVALID_HANDLE_VALUE;
        }

        RUBY_CRITICAL("getStdHandle() : Failed to get received handle value({})", stdHnd);
        return NULL;
    }

    LastErrorStruct getLastError() {
        return {};
    }

}
