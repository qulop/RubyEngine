#pragma once
           
#include <common/TypeTraits.hpp>


// Placeholder
#define KIWI_API

#define KIWI_EXIT_SUCCESS               1
#define KIWI_EXIT_FAILURE               0

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
#define KIWI_ABSTRACT
 
#define KIWI_UNDEFINED_ID               (0)
#define KIWI_BAD_INDEX                  (-1)

#define KIWI_SCOPED_LOCK(mtx)           std::scoped_lock _{ mtx }

#define KIWI_NOTHROW_NEW                new(std::nothrow)

#define KIWI_EMPTY_MACRO                ((void)0)

#define KIWI_BIT(n)                     (1 << n)

#define KIWI_FORWARD_DECLARATIONS(...)  __VA_ARGS__

#define KIWI_IGNORE_RETURN(...)         (Globals::ignore = __VA_ARGS__)

#define KIWI_CREATE_POD(PodName, ...)                                               \
    struct PodName {                                                                \
        __VA_ARGS__                                                                 \
    };                                                                              \
                                                                                    \
    static_assert(std::is_standard_layout_v<PodName> && std::is_trivial_v<PodName>, \
        "The POD type must have both a standard layout and be trivial!");

#define KIWI_CREATE_TEMPLATE_POD(PodName, TemplateExpr, ...)                        \
    template<TemplateExpr>                                                          \
    KIWI_CREATE_POD(PodName, __VA_ARGS__)
