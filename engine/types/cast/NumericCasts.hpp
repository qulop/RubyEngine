#pragma once


#include <utility/Definitions.hpp>

#include <types/TypeTraits.hpp>
#include <types/Concepts.hpp>


namespace Kiwi {
    template<typename...>
    struct CastTraits;

    template<>
    struct CastTraits<Traits::TypeTags::IntegralTag> {
        KIWI_NODISCARD KIWI_FORCEINLINE static Opt<String> ToString(Concepts::Integral auto val) {
            return std::to_string(val);
        }
    };



    using IntCast = CastTraits<Traits::TypeTags::IntegralTag>;
}