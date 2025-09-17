#include "CastTraits.hpp"


namespace Ruby {
    using BasicCast = CastTraits<>;

    using IntCast = CastTraits<Details::Cast::IntegralCastTag>;

    template<typename T, typename... Args>
    using Cast = CastTraits<T, Args...>;
}