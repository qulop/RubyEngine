#pragma once

#include <common/meta/TypeTraits.hpp>
#include <common/cast/Cast.hpp>
#include <common/Errors.hpp>
#include <common/Definitions.hpp>
#include <common/meta/Concepts.hpp>
#include <common/types/Result.hpp>

#include <xxhash.h>
#include <spdlog/fmt/fmt.h>


namespace Kiwi::Details::Hashes::NonCryptographic {
    template<size_t BitDepth>
    struct HashStorage {
        static_assert(Traits::AlwaysFalse::value, "Please, use specialized version of this structure!");
    };


    template<>
    struct HashStorage<32> {
        using value_type = u32;

        value_type value = 0;
    };

    template<>
    struct HashStorage<64> {
        using value_type = u64;

        value_type value = 0;
    };
}


namespace Kiwi {
    template<size_t BitDepth>
        requires (BitDepth ==  32) || (BitDepth == 64)
    class Hash {
    public:
        using HashStorageType = Details::Hashes::NonCryptographic::HashStorage<BitDepth>;
        using value_type = typename HashStorageType::value_type;

    public:
        static Expected<Hash, Error<EGeneralError>> ParseString(StringView str, i32 base = 16) {
            return ParseString32_64(str, base);
        }

        static Opt<Hash> FromData(StringView data) {
            return FromData(data.data(), sizeof(StringView::value_type) * data.size());
        }

        template<Concepts::ContainerSTL T>
        static Opt<Hash> FromData(const T& container) {
            return FromData(container.data(), sizeof(T::value_type) * container.size());
        }

        static Opt<Hash> FromData(const void* data, size_t size) {
            if constexpr (BitDepth == 32) {
                return Hash<32>{ BasicCast::To<u32>(XXH32(data, size, /*seed=*/ 0)) };
            }
            else {  // BitDepth == 64
                return Hash<64>{ BasicCast::To<u64>(XXH64(data, size, /*seed=*/ 0)) };
            }
        }

    public:
        constexpr Hash() = default;

        constexpr explicit Hash(value_type val) :
            m_storage{ val }
        {}

        constexpr Hash(const Hash& other) :
            m_storage(other.m_storage)
        {}

        constexpr Hash(Hash&& other) :
            m_storage(std::exchange(other.m_storage, {}))
        {}

    public:
        KIWI_NODISCARD bool IsEmpty() const {
            return m_storage.value == 0;
        }

        KIWI_NODISCARD value_type GetHashValue() const {
            return m_storage.value;
        }

        KIWI_NODISCARD String ToString() const {
            return String::Format("{:016x}", m_storage.value);
        }

        constexpr Hash& operator=(const Hash& other) = default;
        constexpr Hash& operator=(Hash&& other) noexcept {
            m_storage = std::exchange(other.m_storage, {});

            return *this;
        }

        KIWI_NODISCARD bool operator==(const Hash& other) const noexcept {
            return m_storage.value == other.m_storage.value;
        }

        KIWI_NODISCARD bool operator!=(const Hash& other) const noexcept {
            return m_storage.value != other.m_storage.value;
        }

    private:
        static Result<Hash> ParseString32_64(StringView str, i32 base = 16) {
            u64 val = 0;

            std::from_chars_result res = std::from_chars(str.data(), str.data() + str.size(), val, base);
            if (res.ec != std::errc{}) {
                EGeneralError errorKind;
                String errorDesc = std::make_error_code(res.ec).message();

                if (res.ec == std::errc::invalid_argument) {
                    errorKind = EGeneralError::INVALID_ARGUMENT;
                }
                else {
                    errorKind = EGeneralError::OUT_OF_RANGE;
                }

                return Error{ .kind = errorKind, .desc = errorDesc };
            }

            if (res.ptr != str.data() + str.size()) {
                return Error{
                    .kind = EGeneralError::INVALID_ARGUMENT,
                    .desc = std::format("Invalid character detected at position {}", res.ptr - str.data())
                };
            }

            if constexpr (BitDepth == 32) {
                if (val > (std::numeric_limits<u32>::max)()) {
                    return Error{
                        .kind = EGeneralError::BUFF_OVERFLOW,
                        .desc = std::format("Overflow: {} exceeded specified bit depth of {} bits", str, BitDepth)
                    };
                }
            }

            return Hash{ BasicCast::To<value_type>(val) };
        }

        static Opt<Hash> FromData32(const void* data, size_t size) {
            return Hash{ BasicCast::To<u32>(XXH32(data, size, /*seed=*/ 0)) };
        }

        static Opt<Hash> FromData64(const void* data, size_t size) {
            return Hash{ BasicCast::To<u64>(XXH64(data, size, /*seed=*/ 0)) };
        }

    private:
        HashStorageType m_storage;
    };


    using Hash32 = Hash<32>;
    using Hash64 = Hash<64>;


    template<>
    struct CastTraits<Hash64> {
        KIWI_NODISCARD KIWI_FORCEINLINE static Opt<String> ToString(Hash64 val) {
            return val.ToString();
        }
    };
}


namespace std {
    template<size_t BitDepth>
    struct formatter<Kiwi::Hash<BitDepth>> {
        constexpr auto parse(format_parse_context& ctx) {
            return ctx.begin();
        }

        template<typename TFormatContext>
        auto format(const Kiwi::Hash<BitDepth>& hash, TFormatContext& ctx) const {
            auto hashStr = hash.ToString();

            return std::copy(hashStr.begin(), hashStr.end(), ctx.out());
        }
    };

    template<size_t BitDepth>
    struct hash<Kiwi::Hash<BitDepth>> {
        std::size_t operator()(const Kiwi::Hash<BitDepth>& k) const noexcept {
            return std::hash<typename Kiwi::Hash<BitDepth>::value_type>{}(k.GetHashValue());
        }
    };
}


namespace fmt {
    template<size_t BitDepth>
    struct formatter<Kiwi::Hash<BitDepth>> {
        constexpr auto parse(format_parse_context& ctx) {
            return ctx.begin();
        }

        template<typename TFormatContext>
        auto format(const Kiwi::Hash<BitDepth>& hash, TFormatContext& ctx) const {
            auto hashStr = hash.ToString();

            return std::copy(hashStr.begin(), hashStr.end(), ctx.out());
        }
    };
}