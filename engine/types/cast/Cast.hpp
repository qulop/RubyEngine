#pragma once

#include "CastTraits.hpp"


namespace Kiwi {
    using BasicCast = CastTraits<>;

    template<typename T, typename... Args>
    using Cast = CastTraits<T, Args...>;


    template<typename T>
    KIWI_NODISCARD KIWI_FORCEINLINE T* IsInstanceOf(auto* ptr) {
        return BasicCast::IsInstanceOf<T>(ptr);
    }

    template<typename TTargetType, typename TSourceType>
    requires (!std::is_reference_v<TTargetType>) &&
            std::is_convertible_v<std::decay_t<TSourceType>, TTargetType>
    KIWI_NODISCARD KIWI_FORCEINLINE constexpr TTargetType CastTo(TSourceType&& s) {
        return BasicCast::To<TTargetType>(s);
    }

    template<typename TTargetType, typename TSourceType>
    KIWI_NODISCARD KIWI_FORCEINLINE constexpr TTargetType UnsafeCast(const TSourceType& cur) {
        return BasicCast::UnsafeCast<TTargetType, TSourceType>(cur);
    }

    template<typename TTargetType, typename TSourceType>
    KIWI_NODISCARD KIWI_FORCEINLINE constexpr TTargetType HierarchyCast(const TSourceType& cur) {
        return BasicCast::HierarchyCast<TTargetType, TSourceType>(cur);
    }
}