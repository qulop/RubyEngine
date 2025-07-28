#pragma once

#include <types/TypeTraits.hpp>
#include <types/Concepts.hpp>

#include "Definitions.hpp"
#include "Assert.hpp"
#include "Enum.hpp"

#include <algorithm>


namespace Ruby {
    template<Concepts::Number Tx>
    Opt<Tx> fromChars(std::string_view str, std::chars_format fmt = std::chars_format::general) {
        using ValueType = std::decay_t<Tx>;

        auto val = static_cast<ValueType>(0);
        auto res = std::from_chars_result{ nullptr, std::errc::invalid_argument };

        // `std::from_chars()` doesn't recognize plus sign as the first character
        const auto* begin = (str.front() == '+') ? (str.data() + 1) : str.data();
        const auto* end = (str.data() + str.size());

        if constexpr (std::is_integral_v<ValueType>) {
            res = std::from_chars(begin, end, val);
        }
        else {
            res = std::from_chars(begin, end, val, fmt);
        }

        if (res.ec != std::errc{} || res.ptr == nullptr) {
            return nullopt;
        }

        return val;
    }


    inline Opt<bool> strToBool(std::string_view str) {
        String lowerStr{ str };
        std::ranges::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), tolower);

        return lowerStr == "true";
    }

    RUBY_FORCEINLINE Opt<f32> strToFloat(std::string_view str, std::chars_format fmt = std::chars_format::general) {
        return fromChars<f32>(str, fmt);
    }

    RUBY_FORCEINLINE Opt<f64> strToDouble(std::string_view str, std::chars_format fmt = std::chars_format::general) {
        return fromChars<f64>(str, fmt);
    }

    template<std::integral IntegralType = i32>
    RUBY_FORCEINLINE Opt<IntegralType> strToInt(std::string_view str) {
        return fromChars<IntegralType>(str);
    }

    template<std::integral EnumDerivedType = i32>
    Opt<String> enumValueToString(Concepts::Enum auto en) {
        using EnumType = std::decay_t<decltype(en)>;

        return EnumReflector::Create<EnumType>()
                .GetByValue(static_cast<EnumDerivedType>(en))
                .GetFieldName();
    }

    template<typename Tx>
    Tx* isInstanceOf(auto* ptr) {
        return dynamic_cast<Tx*>(ptr);
    }

    template<typename Targ>
    constexpr Targ cast(const auto& cur) {
        return static_cast<Targ>(cur);
    }
}