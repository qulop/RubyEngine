#pragma once

#include <format>
#include <source_location>

#include <platform/Platform.hpp>
#include <types/TypeTraits.hpp>
#include <types/Singleton.hpp>


namespace Ruby::Details::Assert {
    inline String getAssertionString(std::string_view expr, const String& msg, const std::source_location& loc) {
        auto res = std::format("Assertion failed:\n\t-- Expression: {}\n\t-- File: {}\n\t-- Line: {}\n",
                               expr, 
                               loc.file_name(), 
                               loc.line()
        );

        if(!msg.empty()) {
            res += std::format("\t-- Message: {}\n", msg);
        }
        return res;
    }


    template<typename... Args>
    bool basicAssert(std::string_view expr, std::format_string<Args...> fmt = "", std::source_location loc = std::source_location::current(), Args&&... args) {
        String msg = std::format(std::move(fmt), std::forward<Args>(args)...);
        auto res = getAssertionString(expr, msg, loc);

        Platform::writeInConsole(res);
        std::abort();

        return false;
    }
}


#ifndef RUBY_RELEASE_BUILD
    #define RUBY_ASSERT(expr, fmt, ...)     \
        (static_cast<bool>(expr) || (Ruby::Details::Assert::basicAssert(#expr, fmt, std::source_location::current() __VA_OPT__(,) __VA_ARGS__)))

    #define RUBY_ASSERT_BASIC(expr)         \
        (static_cast<bool>(expr) || (Ruby::Details::Assert::basicAssert(#expr)))
#else
    #define RUBY_ASSERT(expr, msg)      ((void)0)
    #define RUBY_ASSERT_BASIC(expr)     ((void)0)
#endif

#define RUBY_NOT_IMPLEMENTED()  RUBY_ASSERT(Traits::LazyEval<Traits::AlwaysFalse>::value, "An unimplemented function was called")

