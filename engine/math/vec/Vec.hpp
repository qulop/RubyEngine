#pragma once

#include "Vec2.hpp"
#include "Vec3.hpp"
#include "Vec4.hpp"


namespace Ruby {
    template<typename T>
    constexpr T cross(const T& lhs, const T& rhs) {
        return lhs.Cross(rhs);
    }

    template<typename T>
    constexpr T magnitudeOf(const T& v) {
        return v.Magnitude();
    }

    template<typename T>
    constexpr T normalize(const T& v) {
        return v.Normalize();
    }
}
