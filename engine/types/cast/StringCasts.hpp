#pragma once

#include <utility/Definitions.hpp>

#include <types/TypeTraits.hpp>
#include <types/hash/Hash.hpp>

#include <renderer/shaders/ShaderStage.hpp>


namespace Ruby {
    template<typename...>
    struct CastTraits;


    template<>
    struct CastTraits<String> {
        template<Concepts::Number T>
        RUBY_NODISCARD static Opt<T> FromChars(StringView str, std::chars_format fmt = std::chars_format::general) {
            using ValueType = std::decay_t<T>;

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

        RUBY_NODISCARD RUBY_FORCEINLINE static Opt<bool> ToBool(StringView str) {
            auto checkPred = [](StringView lhs, StringView rhs) -> bool {
                return std::ranges::equal(lhs, rhs, [](char lc, char rc) {
                    return std::tolower(lc) == std::tolower(rc);
                });
            };

            if (checkPred(str, "true")) {
                return true;
            }
            else if (checkPred(str, "false")) {
                return false;
            }

            return nullopt;
        }


        RUBY_NODISCARD RUBY_FORCEINLINE static Opt<f32> ToFloat(StringView str, std::chars_format fmt = std::chars_format::general) {
            return FromChars<f32>(str, fmt);
        }

        RUBY_NODISCARD RUBY_FORCEINLINE static Opt<f64> ToDouble(StringView str, std::chars_format fmt = std::chars_format::general) {
            return FromChars<f64>(str, fmt);
        }

        template<Concepts::Integral TIntegralType = i32>
        RUBY_NODISCARD RUBY_FORCEINLINE static Opt<TIntegralType> ToInt(StringView str) {
            return FromChars<TIntegralType>(str);
        }

        RUBY_NODISCARD RUBY_FORCEINLINE static Opt<i32> ToIntI32(StringView str) {
            return FromChars<i32>(str);
        }

        RUBY_NODISCARD RUBY_FORCEINLINE static Opt<u32> ToIntU32(StringView str) {
            return FromChars<u32>(str);
        }

        template<size_t BitDepth>
        RUBY_NODISCARD RUBY_FORCEINLINE static Opt<Hash<BitDepth>> ToHash(StringView str, i32 base = 16) {
            return Hash<BitDepth>::ParseString(str, base);
        }

        RUBY_NODISCARD static Opt<EShaderStage> ToShaderStage(StringView stageName) {
            if      (stageName == "vertex")     return EShaderStage::VERTEX;
            else if (stageName == "geometry")   return EShaderStage::GEOMETRY;
            else if (stageName == "fragment")   return EShaderStage::FRAGMENT;
            else if (stageName == "compute")    return EShaderStage::COMPUTE;

            return nullopt;
        }
    };
}