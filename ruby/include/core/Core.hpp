#pragma once
#ifdef RUBY_WIN32

    #include <cstdint>
    #include <cassert>
    #include <string>
    #include <vector>
    #include <fstream>
    #include <memory>

    #ifdef RUBY_BUILD
        #define RUBY_API                __declspec(dllexport)
    #else   
        #define RUBY_API                __declspec(dllimport)
    #endif  // RUBY_BUILD

    #ifdef __has_cpp_attribute
        #define RUBY_NODISCARD          [[nodiscard]]
        #define RUBY_ASSERT_VAR         [[maybe_unused]]
    #else
        #define RUBY_NODISCARD
        #define RUBY_MAYBE_UNUSED
    #endif  // __has_cpp_attribute

    // Error codes
    #define RUBY_EXIT                   0x00

#endif  // RUBY_WIN32