#pragma once

#include "TypeTraits.hpp"
#include "Concepts.hpp"


namespace Ruby::StringUtils {
    template<std::ranges::input_range Tx>
        requires Concepts::ConvertibleTo<std::ranges::range_value_t<Tx>, String>
    String join(const Tx& rng, char sep = ' ') {
        return std::accumulate(
            std::next(rng.begin()), rng.end(), String{ rng.front() },
            [&](String&& acc, const auto& s) {
                return acc + sep + s;
            }
        );
    }
}