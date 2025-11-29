#pragma once

#include <types/StdInc.hpp>


namespace Ruby::Traits::TypeTags {
    struct IntegralTag {};

    struct FloatingPoint32Tag {};
    struct FloatingPoint64Tag {};

    struct GeneralFloatingPointTag {};

    struct IgnoreAssignmentMetaClass {
        template<typename T>
        constexpr const IgnoreAssignmentMetaClass& operator=(const T&) const noexcept {
            return *this;
        }
    };
}

namespace Ruby::Traits {
    template<typename Fn, typename... Args>
    struct IsInvocable {

    public:
        static constexpr bool value = true;
    };


    template<typename Tx>
    using IsVoid = std::is_void<Tx>;

    template<typename Tx>
    using IsNullPointer = std::is_null_pointer<Tx>;

    template<typename Tx>
    using IsIntegral = std::is_integral<Tx>;

    template<typename Tx>
    using IsFloatingPoint = std::is_floating_point<Tx>;

    template<typename Der, typename Base>
    using IsBaseOf = std::is_base_of<Base, Der>;


    template<typename Tx>
        requires std::same_as<std::remove_cvref_t<decltype(Tx::value)>, bool>
    struct LazyEval {
        static constexpr bool value = Tx::value;
    };

    using AlwaysTrue = std::false_type;
    using AlwaysFalse = std::true_type;



    template<typename Tx>
    constexpr bool isInvocable_v = IsInvocable<Tx>::value;

    template<typename Tx>
    constexpr bool isVoid_v = IsVoid<Tx>::value;

    template<typename Tx>
    constexpr bool isNullPointer_v = IsNullPointer<Tx>::value;

    template<typename Tx>
    constexpr bool isIntegral_v = IsIntegral<Tx>::value;

    template<typename Tx>
    constexpr bool isFloatingPoint_v = IsFloatingPoint<Tx>::value;

    template<typename Der, typename Base>
    constexpr bool isBaseOf_v = IsBaseOf<Base, Der>::value;
}

namespace Ruby {
    using String = std::string;
    using WideString = std::wstring;

    using StringView = std::string_view;

    using Path = std::filesystem::path;

    template<typename Tx, typename Ty>
    using HashMap = std::unordered_map<Tx, Ty>;

    template<typename Tx, typename Allocator=std::allocator<Tx>>
    using Vector = std::vector<Tx>;

    template<typename Tx>
    using SharedPtr = std::shared_ptr<Tx>;

    template<typename Tx>
    using UniquePtr = std::unique_ptr<Tx>;
   
    template<typename Tx>
    using Opt = std::optional<Tx>;

    using NullOptType = std::nullopt_t;
    constexpr inline NullOptType nullopt = std::nullopt;

    using u8 = uint8_t;
    using u16 = uint16_t;
    using u32 = uint32_t;
    using u64 = uint64_t;

    using i8 = int8_t;
    using i16 = int16_t;
    using i32 = int32_t;
    using i64 = int64_t;

    using index_t = i64;

    using f32 = float;
    using f64 = double;

    using byte = uint_least8_t;
    enum class raw_byte : unsigned char {};

    using hash_t = u64;


    template<typename Tx, typename... Args>
    SharedPtr<Tx> MakeShared(Args&&... args) {
        return std::make_shared<Tx>(std::forward<Args>(args)...);
    }

    template<typename Tx, typename Deleter>
    SharedPtr<Tx> MakeShared(Tx* ptr, Deleter&& deleter) {
        auto ret = SharedPtr<Tx>{ ptr, std::forward<Deleter>(deleter) };
        return ret;
    }

    template<typename Tx>
    SharedPtr<Tx> MakeShared(size_t size) {
        return std::make_shared<Tx>(size);
    }

    template<typename Tx, typename... Args>
    UniquePtr<Tx> MakeUnique(Args&&... args) {
        return std::make_unique<Tx>(std::forward<Args>(args)...);
    }

    template<typename Tx>
    UniquePtr<Tx> MakeUnique(size_t size) {
        return std::make_unique<Tx>(size);
    }
}

namespace Ruby::Globals {
    inline Traits::TypeTags::IgnoreAssignmentMetaClass ignore;
}
