#pragma once

#include <string>
#include <vector>
#include <type_traits>
#include <concepts>
#include <unordered_map>

namespace Ruby
{
    using RubyString                        = std::string;

    template<typename Tx, typename Ty>
    using RubyHashMap                       = std::unordered_map<Tx, Ty>;

    template<typename Tx>
    using RubyVector                        = std::vector<Tx>;
    

    using u8 = uint8_t;
    using u16 = uint16_t;
    using u32 = uint32_t;
    using u64 = uint64_t;

    using i8 = int8_t;
    using i16 = int16_t;
    using i32 = int32_t;
    using i64 = int64_t;

}
