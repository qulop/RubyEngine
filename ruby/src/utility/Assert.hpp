/*
    Native implementation of assert() function.

    It has two main macro:
        1) RUBY_ASSERT_WITH_EXPR_AND_MSG_IMPL() - which allow to set assert expression and clarifying message(the
            message will be shown if assert fails);
        2) RUBY_ASSERT_WITH_SINGLE_EXPR_IMPL() - allows to set only assert expression.

    Also, you can change assert behavior using these two macro:
        1) _RUBY_CONFIG_ASSERT_IGNORE_ABORT - if assert fails, std::abort() will not be called - the program will
            continue execution;
        2) _RUBY_CONFIG_ASSERT_IGNORE_OUTPUT - ignore (full)assertion output. If _RUBY_CONFIG_ASSERT_IGNORE_ABORT also
            set, then an error will be completely ignored.
*/

#pragma once

#include <source_location>
#include <types/TypeTraits.hpp>
#include <types/Singleton.hpp>


#if defined(RUBY_MSVC_USED)
    #define __RUBY_FUNC__           __FUNCTION__
#elif defined(RUBY_GCC_USED) || defined(RUBY_CLANG_USED)
    #define __RUBY_FUNC__           __PRETTY_FUNCTION__
#endif


namespace Ruby::Details::Assert {
    bool _rubyAssert(const char* expr, bool assertPrefix,
                     const char* file, u32 line, const char* func, const char* msg=nullptr);

    bool _rubyAssert(const char* expr,
                     bool assertPrefix=true,
                     const char* msg=nullptr,
                     std::source_location&& loc = std::source_location::current());
}


#ifndef _NDEBUG
    #define RUBY_ASSERT_WITH_EXPR_AND_MSG_IMPL(expr, msg, prefix)    \
        (static_cast<bool>(expr) || (Ruby::Details::Assert::_rubyAssert(#expr, prefix, msg)))

    #define RUBY_ASSERT_WITH_SINGLE_EXPR_IMPL(expr, prefix) \
        (static_cast<bool>(expr) || (Ruby::Details::Assert::_rubyAssert(#expr, prefix)))
#else
    #define RUBY_ASSERT_WITH_MSG_IMPL(expr, msg)
    #define RUBY_ASSERT_SINGLE_EXPR_MACRO_IMPL(expr)
#endif


#define RUBY_ASSERT(expr, msg)          RUBY_ASSERT_WITH_EXPR_AND_MSG_IMPL(expr, msg, true)
#define RUBY_ASSERT_BASIC(expr)         RUBY_ASSERT_WITH_SINGLE_EXPR_IMPL(expr, true)

#define RUBY_WRECK(msg)                 RUBY_ASSERT_WITH_EXPR_AND_MSG_IMPL(false, msg, false)
#define RUBY_NOT_IMPLEMENTED            RUBY_WRECK("An unimplemented method(function) was called")
