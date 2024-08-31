#include "Assert.hpp"
#include <types/StdInc.hpp>

#include <platform/Platform.hpp>


namespace Ruby::Details::Assert {
    struct _AssertStruct {  // NOLINT
        const char* msg = "Failed to allocate memory for assertion message: Unknown error was occurred";
        bool isAllocated = false;   // was memory allocated for msg
    };

    _AssertStruct _getFormattedString(bool prefix, const char* expr,
                                                   const char* file, u32 line, const char* func, const char* msg) {
        size_t msgSize = snprintf(nullptr, 0, "%sExpression: %s, File: %s, Line: %d, Function: %s --- %s.\n",
                    (prefix) ? "Assertion Failed: " : "", expr,
                    file, line,
                    (func) ? func : "Unknown", (msg) ? msg : "") + 1;  // + 1 for '\0'

        // TODO: Replace to Ruby::Platform::virtualAlloc()
        char* buffer = new(std::nothrow) char[msgSize];
        if (!buffer)
            return {};

        size_t written = snprintf(buffer, msgSize, "%sExpression: %s, File: %s, Line: %d, Function: %s --- %s.\n",
                    (prefix) ? "Assertion Failed: " : "", expr,
                    file, line,
                    (func) ? func : "", (msg) ? msg : "") + 1;

        if (written != msgSize)
            return {};

        return { .msg=buffer, .isAllocated=true };
     }


     bool _assertBase(const char* expr, bool prefix, const char* file, u32 line, const char* func, const char* msg) {
        auto res = _getFormattedString(prefix, expr, file, line, func, msg);


        // idk how disable this shit...
        // fprintf_s(stderr, res.msg);

        if (res.isAllocated)
            delete res.msg; // TODO: Replace to Ruby::Platform::virtualFree()

        // same...
        // std::abort();

        return false;
     }


    bool _rubyAssert(const char* expr, bool assertPrefix,
                     const char* file, u32 line, const char* func, const char* msg) {
        return _assertBase(expr, assertPrefix, file, line, func, msg);
    }


    bool _rubyAssert(const char* expr, bool assertPrefix, const char* msg, std::source_location&& loc) {
        return _assertBase(expr, assertPrefix, loc.file_name(), loc.line(), loc.file_name(), msg);
    }
}