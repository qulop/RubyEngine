#pragma once


#include <types/Concepts.hpp>
#include "types/cast/Cast.hpp"

#include <utility/Numeric.hpp>


namespace Ruby {
    template<Concepts::Number T>
    class BasicVec4 {
    public:
        using SelfType = BasicVec4;
        
        using value_type = T;
        using ValueType = T;

    public:
        union {
            struct { ValueType x, y, z, w; };
            struct { ValueType r, g, b, a; };
            struct { ValueType s, t, p, q; };
        };

    public:
        static constexpr size_t Size() noexcept {
            return 4;
        }
        
        static constexpr SelfType ZeroVector() noexcept {
            return SelfType{ 0 };
        }

        static constexpr SelfType LeftVector() noexcept {
            return SelfType{ -1, 0, 0, 0 };
        }

        static constexpr SelfType RightVector() noexcept {
            return SelfType{ 1, 0, 0, 0 };
        }

        static constexpr SelfType UpVector() noexcept {
            return SelfType{ 0, 1, 0, 0 };
        }

        static constexpr SelfType DownVector() noexcept {
            return SelfType{ 0, -1, 0, 0 };
        }

    public:
        constexpr BasicVec4() noexcept :
            x(0), y(0), z(0), w(0)
        {}

        constexpr explicit BasicVec4(ValueType scalar) noexcept :
            BasicVec4(scalar, scalar, scalar, scalar)
        {}

        constexpr BasicVec4(ValueType a, ValueType b, ValueType c, ValueType d) noexcept :
            x(a), y(b), z(c), w(d)
        {}

        constexpr BasicVec4(std::array<ValueType, 4> arr) noexcept :
            x(arr[0]), y(arr[1]), z(arr[2]), w(arr[3])
        {}

    public:
        constexpr SelfType& operator=(const SelfType& other) noexcept = default;
        constexpr SelfType& operator=(std::array<ValueType, 4> arr) noexcept {
            x = arr[0];
            y = arr[1];
            y = arr[2];
            w = arr[3];

            return *this;
        }

        constexpr bool operator==(const SelfType& other) const noexcept {
            return x == other.x && y == other.y && z == other.z && w == other.w;
        }

        constexpr bool operator!=(const SelfType& other) const noexcept {
            return !(*this == other);
        }

        constexpr SelfType operator+(const SelfType& other) const noexcept {
            return SelfType(x + other.x, y + other.y, z + other.z, w + other.w);
        }

        constexpr SelfType operator-(const SelfType& other) const noexcept {
            return SelfType(x - other.x, y - other.y, z - other.z, w - other.w);
        }

        constexpr SelfType operator-() const noexcept {
            return SelfType(-x, -y, -z, -w);
        }

        constexpr SelfType operator*(ValueType val) const noexcept {
            return SelfType(x * val, y * val, z * val, w * val);
        }

        constexpr SelfType operator*(const SelfType& other) const noexcept {
            return SelfType(x * other.x, y * other.y, z * other.z, w * other.w);
        }

        constexpr SelfType operator/(ValueType val) const noexcept {
            return SelfType(x / val, y / val, z / val, w / val);
        }

        constexpr SelfType operator/(const SelfType& other) const noexcept {
            return SelfType(x / other.x, y / other.y, z / other.z, w / other.w);
        }

        constexpr SelfType& operator+=(const SelfType& other) noexcept {
            *this = *this + other;

            return *this;
        }

        constexpr SelfType& operator+=(ValueType val) noexcept {
            *this = *this + val;

            return *this;
        }

        constexpr SelfType& operator-=(const SelfType& other) noexcept {
            *this = *this - other;

            return *this;
        }

        constexpr SelfType& operator-=(ValueType val) noexcept {
            *this = *this - val;

            return *this;
        }

        constexpr SelfType& operator*=(const SelfType& other) noexcept {
            *this = *this * other;

            return *this;
        }

        constexpr SelfType& operator*=(ValueType val) noexcept {
            *this = *this * val;

            return *this;
        }

        constexpr SelfType& operator/=(const SelfType& other) noexcept {
            *this = *this / other;

            return *this;
        }

        constexpr SelfType& operator/=(ValueType val) noexcept {
            *this = *this / val;

            return *this;
        }

    public:
        constexpr std::array<ValueType, 4> ToArray() const noexcept {
            return { x, y, z, w };
        }

        constexpr float Magnitude() const noexcept {
            return std::sqrt(Numeric::pow2(x) + Numeric::pow2(y) + Numeric::pow2(z) + Numeric::pow2(w));
        }

        constexpr float Dot(const SelfType& other) const noexcept {
            return (x * other.x) + (y * other.y) + (z * other.z) + (w * other.w);
        }

        constexpr SelfType Cross(const SelfType& other) const noexcept {
            return *this * other;
        }

        constexpr ValueType ValuedDot(const SelfType& other) const noexcept {
            return BasicCast::To<ValueType>(Dot(other));
        }
    };


    using Vec4 = BasicVec4<f32>;
    using IVec4 = BasicVec4<i32>;
    using UVec4 = BasicVec4<u32>;
    using BVec4 = BasicVec4<bool>;
    using DVec4 = BasicVec4<f64>;
    using Point4D = Vec4;
}
