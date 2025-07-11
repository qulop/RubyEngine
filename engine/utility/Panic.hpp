#pragma once

#include <types/TypeTraits.hpp>


namespace Ruby::Details::Panic {
    template<typename... Args>
    void _runtimePanic(std::format_string<Args...> fmt, std::source_location loc = std::source_location::current(), Args&&... args) {
        String msg = std::format(fmt, std::forward<Args>(args)...);

        std::abort();
    }

#if __cplusplus >= 202600L
    // Using of non-literal values(like result of `std::string_view::data()` in the second parameter of `static_assert()` available only since C++26
    consteval void _staticPanic(std::string_view msg) {
        static_assert(Traits::LazyEval<Traits::AlwaysFalse>::value, msg.data());    
    }
#endif
}

// IDK why we need this
#define RUBY_STATIC_PANIC(msg)          static_assert(Ruby::Traits::LazyEval<Ruby::Traits::AlwaysFalse>::value, msg);
#define RUBY_RUNTIME_PANIC(msg, ...)    Ruby::Details::Panic::_runtimePanic(msg, __VA_OPT__(,) __VA_ARGS__)
#define RUBY_RUNTIME_PANIC_MSG(msg)     Ruby::Details::Panic::_runtimePanic(msg)
