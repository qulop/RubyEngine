#pragma once

#include <types/TypeTraits.hpp>
#include <types/Concepts.hpp>

#include <utility/Definitions.hpp>
#include <utility/Assert.hpp>
#include <utility/Enum.hpp>

#include <algorithm>


namespace Ruby::Details::Cast {
    struct IntegralCastTag {};
}


namespace Ruby {
    template<typename...>
    struct CastTraits {
        static_assert(Traits::AlwaysFalse::value, "Base `CastTraits` specialization was called for unsopported type. You can create your own specialization for this type");
    };

    template<>
    struct CastTraits<> {
        template<typename Tx>
        RUBY_NODISCARD RUBY_FORCEINLINE static Tx* IsInstanceOf(auto* ptr) {
            return dynamic_cast<Tx*>(ptr);
        }

        template<typename TTargetType, typename TSourceType>
        RUBY_NODISCARD static constexpr TTargetType To(const TSourceType& cur) {
            return static_cast<TTargetType>(cur);
        }

        template<typename TTargetType, typename TSourceType>
        RUBY_NODISCARD static constexpr TTargetType UnsafeCast(const TSourceType& cur) {
            return reinterpret_cast<TTargetType>(cur);
        }

        template<typename TTargetType, typename TSourceType>
            requires Concepts::IsBaseOf<TTargetType, TSourceType> || Concepts::DerivedFrom<TTargetType, TSourceType>
        RUBY_NODISCARD static constexpr TTargetType HierarchyCast(const TSourceType& cur) {
            return CastTraits<>::To<TTargetType>(cur);
        }
    };


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

        RUBY_NODISCARD RUBY_FORCEINLINE static Opt<hash_t> ToHash(StringView str, i32 base = 16) {
            hash_t val = 0;

            auto res = std::from_chars(str.data(), str.data() + str.size(), val, base);
            return (res.ec == std::errc{} && res.ptr == str.data() + str.size()) ? Opt<hash_t>{ val } : nullopt;
        }
    };


    template<>
    struct CastTraits<Details::Cast::IntegralCastTag> {
        RUBY_NODISCARD RUBY_FORCEINLINE static Opt<String> ToString(Concepts::Integral auto val) {
            return std::to_string(val);
        }
    };
}