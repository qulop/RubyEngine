#pragma once
           
#include <types/TypeTraits.hpp>


// Placeholder
#define RUBY_API

#define RUBY_NODISCARD                  [[nodiscard]]
#define RUBY_MAYBE_UNUSED               [[maybe_unused]]
#define RUBY_FALLTHROUGH                [[fallthrough]]
#define RUBY_NORETURN                   [[noreturn]]
#define RUBY_UNLIKELY                   [[unlikely]]
#define RUBY_LIKELY                     [[likely]]
#define RUBY_DEPRECATED                 [[deprecated]]

#ifdef _NDEBUG            
    #define RUBY_LOG_LEVEL                   spdlog::level::debug
#else
    #define RUBY_LOG_LEVEL                   spdlog::level::trace
#endif

#ifdef RUBY_MSVC_USED
    #define RUBY_FORCEINLINE            __forceinline
#else
    #define RUBY_FORCEINLINE            inline
#endif

#define RUBY_MAKE_STRING(x)             #x
#define RUBY_SWITCH_BOOL(target)        target = !target

#define RUBY_INTERFACE                  struct
#define RUBY_ABSTRACT             
 
#define loop                            while (true)

#define RUBY_UNDEFINED_ID               (0)
#define RUBY_BAD_INDEX                  (-1)

#define RUBY_SCOPED_LOCK(mtx)           std::scoped_lock _{ mtx }

#define RUBY_NOTHROW_NEW                new(std::nothrow)

#define RUBY_EMPTY_MACRO                ((void)0)

#define RUBY_BIT(n)                     (1 << n)
