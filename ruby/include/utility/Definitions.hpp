#pragma once
           
#include <memory>           
#include <cstdio>   
#include <cassert>   
#include <ctype.h>          
#include <functional>    
#include "TypeTraits.hpp"      


#ifdef _MSC_VER
    #define RUBY_MSVC_USED
#elif defined(__clang__)
    #define RUBY_CLANG_USED
#elif defined(__GNUC__) || defined(__GNUG__)
    #define RUBY_GCC_USED
#endif


#ifdef RUBY_ENGINE_BUILD           
    #define RUBY_API                    __declspec(dllexport)
#else               
    #define RUBY_API                    __declspec(dllimport)
#endif 

#define RUBY_NODISCARD              [[nodiscard]]
#define RUBY_MAYBE_UNUSED           [[maybe_unused]]
#define RUBY_FALLTHROUGH            [[fallthrough]]
#define RUBY_NORETURN               [[noreturn]]

#ifdef _NDEBUG            
    #define LOG_LEVEL                   spdlog::level::info
#else
    #define LOG_LEVEL                   spdlog::level::debug
#endif

#ifdef RUBY_MSVC_USED
    #define RUBY_FORCEINLINE            __forceinline
#else
    #define RUBY_FORCEINLINE            inline
#endif

                            
#define RUBY_ASSERT(expr, msg)          assert(expr && msg)
#define RUBY_ASSERT_1(expr)             assert(expr)
#define RUBY_WRECK(msg)                 RUBY_ASSERT(false, msg);

#define RUBY_MAKE_STRING(x)             #x
#define RUBY_SWITCH_BOOL(target)        target = !target

#define interface                       class
#define abstract

const size_t g_Npos                     = std::numeric_limits<size_t>::max();
