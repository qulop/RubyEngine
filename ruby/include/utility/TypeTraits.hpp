#pragma once

#include <vector>
#include <string>
#include <concepts>
#include <type_traits>
#include <string_view>
#include <unordered_map>
#include <filesystem>

#define LOCK_MUTEX(MutexType)               std::lock_guard<MutexType> lock{ m_mutex }

namespace Ruby
{
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
