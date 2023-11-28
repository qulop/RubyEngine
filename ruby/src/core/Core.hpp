#pragma once

#pragma warning(disable : 4251)
            
#include <string>           
#include <vector>           
#include <memory>           
#include <ctype.h>          
#include <cassert>   
#include <cstdio>   
#include <functional>    


namespace Ruby
{
    using RubyString                        = std::string;
                
    #ifdef RUBY_BUILD           
        #define RUBY_API                    __declspec(dllexport)
    #else               
        #define RUBY_API                    __declspec(dllimport)
    #endif  // RUBY_BUILD           
                
    #ifdef __has_cpp_attribute          
        #define RUBY_NODISCARD              [[nodiscard]]
        #define RUBY_ASSERT_VAR             [[maybe_unused]]
    #else           
        #define RUBY_NODISCARD          
        #define RUBY_ASSERT_VAR           
    #endif  // __has_cpp_attribute          
                                
    #define RUBY_ASSERT(expr)               assert(expr)
    #define RUBY_STATIC_ASSERT(expr, msg)   static_assert(expr, #msg)
}
