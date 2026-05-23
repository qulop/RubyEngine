#pragma once

#include <cstdint>


// Placeholder
#define KIWI_API

#define KIWI_EXIT_SUCCESS               0
#define KIWI_EXIT_FAILURE               1

#define KIWI_NODISCARD                  [[nodiscard]]
#define KIWI_MAYBE_UNUSED               [[maybe_unused]]
#define KIWI_FALLTHROUGH                [[fallthrough]]
#define KIWI_NORETURN                   [[noreturn]]
#define KIWI_UNLIKELY                   [[unlikely]]
#define KIWI_LIKELY                     [[likely]]
#define KIWI_DEPRECATED                 [[deprecated]]

#ifdef _NDEBUG            
    #define KIWI_LOG_LEVEL                   spdlog::level::debug
#else
    #define KIWI_LOG_LEVEL                   spdlog::level::trace
#endif

#ifdef KIWI_MSVC_USED
    #define KIWI_FORCEINLINE            __forceinline
#else
    #define KIWI_FORCEINLINE            inline
#endif

#define KIWI_MAKE_STRING(x)             #x
#define KIWI_SWITCH_BOOL(target)        target = !target

#define KIWI_INTERFACE                  struct

#define KIWI_UNDEFINED_ID               (0)
#define KIWI_BAD_INDEX                  (-1)

#define KIWI_SCOPED_LOCK(mtx)           std::scoped_lock _{ mtx }

#define KIWI_NOTHROW_NEW                new(std::nothrow)

#define KIWI_EMPTY_MACRO                ((void)0)

#define KIWI_BIT(n)                     (1 << n)

#define KIWI_IGNORE_RETURN(...)         (Globals::ignore = __VA_ARGS__)


namespace Kiwi {
    using u8 = uint8_t;
    using u16 = uint16_t;
    using u32 = uint32_t;
    using u64 = uint64_t;

    using i8 = int8_t;
    using i16 = int16_t;
    using i32 = int32_t;
    using i64 = int64_t;
    using index_t = size_t;

    using f32 = float;
    using f64 = double;

    using byte = uint_least8_t;
    enum class raw_byte : unsigned char {};

    using hash_t = u64;
}