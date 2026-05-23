#pragma once

#include <format>
#include <source_location>

#include <common/Definitions.hpp>
#include <common/types/String.hpp>

namespace Kiwi {
    class Debug final {
    public:
        template<typename... Args>
        static void AssertImpl(StringView expr, std::format_string<Args...> fmt, std::source_location loc = std::source_location::current(), Args&&... args) {
            const String errMsg = String::Format(fmt, std::forward<Args>(args)...);
            HandleAssert(expr, errMsg.ToStringView(), loc);
        }


        static void AssertImplBasic(StringView expr, std::source_location loc = std::source_location::current()) {
            HandleAssert(expr, "", loc);
        }

    private:
        static void HandleAssert(StringView expr, StringView errMsg, std::source_location loc);
    };

}


#ifdef KIWI_DEBUG_BUILD
    #define KIWI_ASSERT(expr, fmt, ...)                                                                             \
        {                                                                                                           \
            if (!(expr)) KIWI_UNLIKELY {                                                                            \
                Kiwi::Debug::AssertImpl(#expr, fmt, std::source_location::current() __VA_OPT__(,) __VA_ARGS__);     \
            }                                                                                                       \
        }

    #define KIWI_ASSERT_BASIC(expr)                                                                                 \
        {                                                                                                           \
            if (!(expr)) KIWI_UNLIKELY {                                                                            \
                Kiwi::Debug::AssertImplBasic(#expr, std::source_location::current());                               \
            }                                                                                                       \
        }

    #define KIWI_ENSURE(expr)   \
        KIWI_ASSERT(expr, "Ensure expression failed!")
#else
    #define KIWI_ASSERT(expr, fmt, ...)     KIWI_EMPTY_MACRO
    #define KIWI_ASSERT_BASIC(expr)         KIWI_EMPTY_MACRO
    #define KIWI_ENSURE(expr)             KIWI_EMPTY_MACRO
#endif


// TODO: Replace `KIWI_ASSERT()` with something else. We can't use `KIWI_ASSERT()` here, because this macro is debug-only
#define KIWI_NOT_IMPLEMENTED()  \
    KIWI_ASSERT(Traits::LazyEval<Traits::AlwaysFalse>::value, "An unimplemented function was called")

