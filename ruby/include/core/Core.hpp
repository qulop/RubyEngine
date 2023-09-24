#pragma once
            
#include <string>           
#include <vector>           
#include <ctype.h>          
#include <cassert>          
            
#ifdef RUBY_BUILD           
    #define RUBY_API                            __declspec(dllexport)
#else               
    #define RUBY_API                            __declspec(dllimport)
#endif  // RUBY_BUILD           
            
#ifdef __has_cpp_attribute          
    #define RUBY_NODISCARD                      [[nodiscard]]
    #define RUBY_ASSERT_VAR                     [[maybe_unused]]
#else           
    #define RUBY_NODISCARD          
    #define RUBY_MAYBE_UNUSED           
#endif  // __has_cpp_attribute          
            
#if defined(_NDEBUG)            
    #define LOG_LEVEL                               spdlog::level::info
#else
    #define LOG_LEVEL                               spdlog::level::debug
#endif  // !defined(_NDEBUG)
            
#define RUBY_ASSERT(expr)                       assert(expr)
