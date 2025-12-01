#pragma once

#include <format>
#include <source_location>

#include <platform/io/SystemConsole.hpp>
#include <types/TypeTraits.hpp>


namespace Kiwi::Details::Assert {
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
        auto res = std::move(getAssertionString(expr, msg, loc));

        Console::WriteLine(res);
        std::abort();

        return false;
    }
}


#ifdef KIWI_DEBUG_BUILD
    #define KIWI_ASSERT(expr, fmt, ...)     \
        (static_cast<bool>(expr) || (Kiwi::Details::Assert::basicAssert(#expr, fmt, std::source_location::current() __VA_OPT__(,) __VA_ARGS__)))

    #define KIWI_ASSERT_BASIC(expr)         \
        (static_cast<bool>(expr) || (Kiwi::Details::Assert::basicAssert(#expr)))
#else
    #define KIWI_ASSERT(expr, msg)      ((void)0)
    #define KIWI_ASSERT_BASIC(expr)     ((void)0)
#endif

#define KIWI_NOT_IMPLEMENTED()  KIWI_ASSERT(Traits::LazyEval<Traits::AlwaysFalse>::value, "An unimplemented function was called")

