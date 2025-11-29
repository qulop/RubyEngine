#pragma once
           
#include <types/TypeTraits.hpp>


// Placeholder
#define RUBY_API

#define RUBY_EXIT_SUCCESS               1
#define RUBY_EXIT_FAILURE               0

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
 
#define RUBY_UNDEFINED_ID               (0)
#define RUBY_BAD_INDEX                  (-1)

#define RUBY_SCOPED_LOCK(mtx)           std::scoped_lock _{ mtx }

#define RUBY_NOTHROW_NEW                new(std::nothrow)

#define RUBY_EMPTY_MACRO                ((void)0)

#define RUBY_BIT(n)                     (1 << n)

#define RUBY_FORWARD_DECLARATIONS(...)  __VA_ARGS__

#define RUBY_IGNORE_RETURN(...)         (Globals::ignore = __VA_ARGS__)

#define RUBY_CREATE_POD(PodName, ...)                                               \
    struct PodName {                                                                \
        __VA_ARGS__                                                                 \
    };                                                                              \
                                                                                    \
    static_assert(std::is_standard_layout_v<PodName> && std::is_trivial_v<PodName>, \
        "The POD type must have both a standard layout and be trivial!");

#define RUBY_CREATE_TEMPLATE_POD(PodName, TemplateExpr, ...)                        \
    template<TemplateExpr>                                                          \
    RUBY_CREATE_POD(PodName, __VA_ARGS__)