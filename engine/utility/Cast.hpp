#pragma once

#include <types/TypeTraits.hpp>
#include <types/Concepts.hpp>

#include "Definitions.hpp"
#include "Assert.hpp"
#include "Enum.hpp"

#include <algorithm>


namespace Ruby {
    class Cast {
    public:
        template<typename Tx>
        RUBY_NODISCARD RUBY_FORCEINLINE static Tx* IsInstanceOf(auto* ptr) {
            return dynamic_cast<Tx*>(ptr);
        }

        template<typename TargetType, typename SourceType>
        RUBY_NODISCARD static constexpr TargetType To(const SourceType& cur) {
            return static_cast<TargetType>(cur);
        }

    public:
        template<Concepts::Number Tx>
        RUBY_NODISCARD static Opt<Tx> FromChars(std::string_view str, std::chars_format fmt = std::chars_format::general) {
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

        RUBY_NODISCARD static inline Opt<bool> StringToBool(std::string_view str) {
            String lowerStr{ str };
            std::ranges::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), tolower);

            return lowerStr == "true";
        }

        RUBY_NODISCARD RUBY_FORCEINLINE static Opt<f32> StringToFloat(std::string_view str, std::chars_format fmt = std::chars_format::general) {
            return FromChars<f32>(str, fmt);
        }

        RUBY_NODISCARD RUBY_FORCEINLINE static Opt<f64> StringToDouble(std::string_view str, std::chars_format fmt = std::chars_format::general) {
            return FromChars<f64>(str, fmt);
        }

        template<Concepts::Integral IntegralType = i32>
        RUBY_NODISCARD RUBY_FORCEINLINE static Opt<IntegralType> StringToInt(std::string_view str) {
            return FromChars<IntegralType>(str);
        }

        RUBY_NODISCARD RUBY_FORCEINLINE static Opt<String> IntToString(Concepts::Integral auto val) {
            return std::to_string(val);
        }

        template<std::integral EnumDerivedType = i32>
        RUBY_NODISCARD static Opt<String> EnumToString(Concepts::Enum auto en) {
            using EnumType = std::decay_t<decltype(en)>;

            return EnumReflector::Create<EnumType>()
                .GetByValue(static_cast<EnumDerivedType>(en))
                .GetFieldName();
        }
    };
}