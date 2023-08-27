#pragma once
#ifdef RUBY_WIN32

#include <cstdint>

#ifdef RUBY_BUILD
    #define RUBY_API  __declspec(dllexport)
#else
    #define RUBY_API  __declspec(dllimport)
#endif  // RUBY_BUILD

#ifdef __has_cpp_attribute
    #define RUBY_NODISCARD [[nodiscard]]
    #define RUBY_MAYBE_UNUSED [[maybe_unused]]
#else
    #define RUBY_NODISCARD
    #define RUBY_MAYBE_UNUSED
#endif  // __has_cpp_attribute

#endif  // RUBY_WIN32