#pragma once


#include <utility/Definitions.hpp>

#include <types/TypeTraits.hpp>


namespace Ruby {
    template<typename...>
    struct CastTraits;

    template<>
    struct CastTraits<Traits::TypeTags::IntegralTag> {
        RUBY_NODISCARD RUBY_FORCEINLINE static Opt<String> ToString(Concepts::Integral auto val) {
            return std::to_string(val);
        }
    };



    using IntCast = CastTraits<Traits::TypeTags::IntegralTag>;
}