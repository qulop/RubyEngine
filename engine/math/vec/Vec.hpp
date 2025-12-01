#pragma once

#include "Vec2.hpp"
#include "Vec3.hpp"
#include "Vec4.hpp"


namespace Kiwi {
    template<typename T>
    constexpr T Cross(const T& lhs, const T& rhs) {
        return lhs.Cross(rhs);
    }

    template<typename T>
    constexpr T MagnitudeOf(const T& v) {
        return v.Magnitude();
    }

    template<typename T>
    constexpr T Normalize(const T& v) {
        return v.Normalize();
    }
}
