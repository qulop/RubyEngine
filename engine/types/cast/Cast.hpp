#pragma once

#include "CastTraits.hpp"


namespace Kiwi {
    using BasicCast = CastTraits<>;

    template<typename T, typename... Args>
    using Cast = CastTraits<T, Args...>;


    template<typename TTargetType, typename TSourceType>
    KIWI_FORCEINLINE constexpr TTargetType CastTo(TSourceType&& s) {
        return BasicCast::To<TTargetType>(s);
    }
}