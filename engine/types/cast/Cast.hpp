#pragma once

#include "CastTraits.hpp"


namespace Kiwi {
    using BasicCast = CastTraits<>;

    template<typename T, typename... Args>
    using Cast = CastTraits<T, Args...>;
}