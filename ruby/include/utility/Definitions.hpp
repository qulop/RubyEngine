#pragma once
           
#include <memory>           
#include <cstdio>   
#include <cassert>   
#include <ctype.h>          
#include <functional>    
#include "TypeTraits.hpp"           


#ifdef RUBY_BUILD           
    #define RUBY_API                    __declspec(dllexport)
#else               
    #define RUBY_API                    __declspec(dllimport)
#endif  // RUBY_BUILD           
            
#ifdef __has_cpp_attribute          
    #define RUBY_NODISCARD              [[nodiscard]]
    #define RUBY_ASSERT_VAR             [[maybe_unused]]
    #define RUBY_FALLTHROUGH            [[fallthrough]]
    #define RUBY_NORETURN               [[noreturn]]
#else           
    #define RUBY_NODISCARD          
    #define RUBY_ASSERT_VAR 
    #define RUBY_FALLTHROUGH
    #define RUBY_NORETURN          
#endif  // __has_cpp_attribute    

#ifdef _NDEBUG            
    #define LOG_LEVEL                   spdlog::level::info
#else
    #define LOG_LEVEL                   spdlog::level::debug
#endif  // _NDEBUG

                            
#define RUBY_ASSERT(expr, msg)          assert(expr && msg)
#define RUBY_ASSERT(expr)               assert(expr)

const size_t g_Npos = SIZE_MAX;
