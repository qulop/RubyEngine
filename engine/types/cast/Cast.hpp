#pragma once

#include "CastTraits.hpp"


namespace Ruby {
    using BasicCast = CastTraits<>;

    template<typename T, typename... Args>
    using Cast = CastTraits<T, Args...>;
}