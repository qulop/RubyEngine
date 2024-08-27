#include "Assert.hpp"
#include "StdInc.hpp"

#include <platform/Platform.hpp>


namespace Ruby::Details::Utility {
     RUBY_FORCEINLINE const char* _getFormattedString(bool prefix, const char* expr,
                                                   const char* file, u32 line, const char* func, const char* msg) {
        size_t msgSize = snprintf(nullptr, 0, "%sExpression: %s, File: %s, Line: %d, Function: %s --- %s.",
                    (prefix) ? "Assertion Failed: " : "",
                    expr,
                    file,
                    line,
                    (func) ? func : "Unknown",
                    (msg) ? msg : "") + 1;  // + 1 for '\0'

        char* buffer = new char(msgSize);
        if (!buffer)
            return nullptr;

        size_t written = snprintf(buffer, msgSize, "%sExpression: %s, File: %s, Line: %d, Function: %s --- %s.",
                    (prefix) ? "Assertion Failed: " : "",
                    expr,
                    file,
                    line,
                    (func) ? func : "",
                    (msg) ? msg : "");

        if (written != msgSize)
            return nullptr;

        return buffer;
     }


     RUBY_FORCEINLINE bool _assertBase(const char* expr, bool prefix, const char* file, u32 line,
                                       const char* func, const char* msg) {
        const char* res = _getFormattedString(prefix, expr, file, line, func, msg);
        if (res) {
            fprintf_s(stderr, res);
            delete res;
        }
        else {
            fprintf_s(stderr, "Failed to allocate memory for assertion message: Unknown error was occurred");
        }

        #ifndef _RUBY_CONFIG_ASSERT_IGNORE_ABORT
            std::abort();
        #endif

        return false;
     }


    bool _rubyAssert(const char* expr, const char* file, bool assertPrefix, u32 line, const char* func,
                     const char* msg) {
        return _assertBase(expr, assertPrefix, file, line, func, msg);
    }


    bool _rubyAssert(const char* expr, const char* msg, bool assertPrefix, std::source_location&& loc) {
        return _assertBase(expr, assertPrefix, loc.file_name(), loc.line(), loc.file_name(), msg);
    }
}