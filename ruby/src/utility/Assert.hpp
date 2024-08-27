#pragma once

#include <source_location>


#ifdef RUBY_MSVC_USED
    #define __RUBY_FUNC__           __FUNCTION__
#elifdef RUBY_GCC_USED
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