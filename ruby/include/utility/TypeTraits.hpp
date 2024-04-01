#pragma once

#include <StdInc.hpp>

#define LOCK_MUTEX(MutexType)               std::lock_guard<MutexType> lock{ m_mutex }

namespace Ruby
{
    namespace Traits::Concepts
    {
        template<typename Tx>
        concept Iterable = requires(std::ranges::range_value_t<Tx> rng)
        {
            rng.begin(); rng.end();
            rng.Begin(); rng.End();
        };
    }

    using RubyString                        = std::string;
    using RubyStringView                    = std::string_view;

    template<typename Tx, typename Ty>
    using RubyHashMap                       = std::unordered_map<Tx, Ty>;

    template<typename Tx>
    using RubyVector                        = std::vector<Tx>;
   
    using RubyPath                          = std::filesystem::path;

    using u8                                = uint8_t;
    using u16                               = uint16_t;
    using u32                               = uint32_t;
    using u64                               = uint64_t;

    using i8                                = int8_t;
    using i16                               = int16_t;
    using i32                               = int32_t;
    using i64                               = int64_t;

    using f32                               = float;
    using f64                               = double;

    // C-String
    using cstr                              = const char*;

    template<typename Ret, typename... Args>
    struct NumberOfArguments
    {
        static constexpr size_t Value = sizeof...(Args);
    };

    template<typename Ret, typename... Args>
    constexpr size_t g_NumberOfArguments_v = NumberOfArguments<Ret, Args...>::Value;
}
