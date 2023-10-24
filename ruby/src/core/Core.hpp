#pragma once

#pragma warning(disable : 4251)
            
#include <string>           
#include <vector>           
#include <ctype.h>          
#include <cassert>   
#include <cstdio>   
#include <functional>    



// Assert implementation
#ifdef _NDEBUG
            RVN_ASSERT(expr, msg)
#else
    #define RVN_ASSERT(expr, msg)       if (!expr)                                                                                              \
                                        {                                                                                                       \
                                            fprintf_s(stderr, "Assertion failed: %s. In file: %s, on line %d.\n", #expr, __FILE__, __LINE__);   \
                                            fprintf_s(stderr, "Message: %s\n", #msg);                                                           \
                                        }
#endif
// ---------



            
#ifdef RUBY_BUILD           
    #define RUBY_API                    __declspec(dllexport)
#else               
    #define RUBY_API                    __declspec(dllimport)
#endif  // RUBY_BUILD           
            
#ifdef __has_cpp_attribute          
    #define RUBY_NODISCARD              [[nodiscard]]
    #define RUBY_MAYBE_UNUSED           [[maybe_unused]]
#else           
    #define RUBY_NODISCARD          
    #define RUBY_ASSERT_VAR           
#endif  // __has_cpp_attribute          
            
#ifdef _NDEBUG            
    #define LOG_LEVEL                   spdlog::level::info
#else
    #define LOG_LEVEL                   spdlog::level::debug
#endif  // _NDEBUG
            
#define RUBY_ASSERT(expr)               assert(expr)
#define RUBY_STATIC_ASSERT(expr, msg)   static_assert(expr, #msg)
