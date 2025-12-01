#pragma once

#include <utility/Definitions.hpp>
#include <utility/Assert.hpp>

#include <types/TypeTraits.hpp>
#include <types/hash/Hash.hpp>

#include <renderer/shaders/ShaderStage.hpp>


namespace Kiwi {
    template<typename...>
    struct CastTraits;


    template<>
    struct CastTraits<String> {
        template<Concepts::Number T>
        KIWI_NODISCARD static Opt<T> FromChars(StringView str, std::chars_format fmt = std::chars_format::general) {
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

        KIWI_NODISCARD KIWI_FORCEINLINE static Opt<String> FromWideString(const WideString& wstr) {
            if constexpr (std::same_as<WideString, std::wstring>) {
                return std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(wstr);
            }
            else {
                KIWI_ASSERT(false, "You forgot to adapt this function for our custom WideString type");
                return nullopt;
            }
        }

        KIWI_NODISCARD KIWI_FORCEINLINE static Opt<bool> ToBool(StringView str) {
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


        KIWI_NODISCARD KIWI_FORCEINLINE static Opt<f32> ToFloat(StringView str, std::chars_format fmt = std::chars_format::general) {
            return FromChars<f32>(str, fmt);
        }

        KIWI_NODISCARD KIWI_FORCEINLINE static Opt<f64> ToDouble(StringView str, std::chars_format fmt = std::chars_format::general) {
            return FromChars<f64>(str, fmt);
        }

        template<Concepts::Integral TIntegralType = i32>
        KIWI_NODISCARD KIWI_FORCEINLINE static Opt<TIntegralType> ToInt(StringView str) {
            return FromChars<TIntegralType>(str);
        }

        KIWI_NODISCARD KIWI_FORCEINLINE static Opt<i32> ToIntI32(StringView str) {
            return FromChars<i32>(str);
        }

        KIWI_NODISCARD KIWI_FORCEINLINE static Opt<u32> ToIntU32(StringView str) {
            return FromChars<u32>(str);
        }

        KIWI_NODISCARD KIWI_FORCEINLINE static Opt<u32> ToIntI64(StringView str) {
            return FromChars<i64>(str);
        }

        template<size_t BitDepth>
        KIWI_NODISCARD KIWI_FORCEINLINE static Opt<Hash<BitDepth>> ToHash(StringView str, i32 base = 16) {
            return Hash<BitDepth>::ParseString(str, base);
        }

        KIWI_NODISCARD static Opt<EShaderStage> ToShaderStage(StringView stageName) {
            if      (stageName == "vertex")     return EShaderStage::VERTEX;
            else if (stageName == "geometry")   return EShaderStage::GEOMETRY;
            else if (stageName == "fragment")   return EShaderStage::FRAGMENT;
            else if (stageName == "compute")    return EShaderStage::COMPUTE;

            return nullopt;
        }
    };
}