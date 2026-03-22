#pragma once

#include <common/meta/TypeTraits.hpp>
#include <common/meta/Concepts.hpp>

#include <common/Definitions.hpp>


namespace Kiwi {
    template<typename...>
    struct CastTraits {
        static_assert(Traits::AlwaysFalse::value, "Base `CastTraits` specialization was called for unsupported type. You can create your own specialization for this type");
    };

    template<>
    struct CastTraits<> {
        template<typename Tx>
        KIWI_NODISCARD KIWI_FORCEINLINE static Tx* IsInstanceOf(auto* ptr) {
            return dynamic_cast<Tx*>(ptr);
        }

        template<typename TTargetType, typename TSourceType>
        KIWI_NODISCARD KIWI_FORCEINLINE static constexpr TTargetType To(const TSourceType& cur) {
            return static_cast<TTargetType>(cur);
        }

        template<typename TTargetType, typename TSourceType>
        KIWI_NODISCARD KIWI_FORCEINLINE static constexpr TTargetType UnsafeCast(const TSourceType& cur) {
            return reinterpret_cast<TTargetType>(cur);
        }

        template<typename TTargetType, typename TSourceType>
            requires
                Concepts::IsBaseOf<std::remove_pointer_t<TTargetType>, std::remove_pointer_t<TSourceType>> ||
                Concepts::DerivedFrom<std::remove_pointer_t<TTargetType>, std::remove_pointer_t<TSourceType>>
        KIWI_NODISCARD KIWI_FORCEINLINE static constexpr TTargetType HierarchyCast(const TSourceType& cur) {
            return CastTraits<>::To<TTargetType>(cur);
        }
    };
}


namespace Kiwi::Concepts {
    template<typename T>
    concept CanBeCastedToString = requires (T t) {
        { CastTraits<T>::ToString(t) } -> std::convertible_to<String>;
    };
}