#pragma once

#include <types/TypeTraits.hpp>
#include <types/Concepts.hpp>
#include "types/cast/Cast.hpp"

#include <utility/Numeric.hpp>



namespace Ruby {
    template<Concepts::Number T>
    class BasicVec2 {
    public:
        using SelfType = BasicVec2;

        using value_type = T;
        using ValueType = T;

    public:
        union {
            struct { ValueType x, y; };
            struct { ValueType r, g; };
            struct { ValueType s, t; };
        };

    public:
        static constexpr size_t Size() noexcept {
            return 2;
        }

        static constexpr SelfType ZeroVector() noexcept {
            return SelfType{ 0, 0 };
        }

        static constexpr SelfType LeftVector() noexcept {
            return SelfType{ -1, 0 };
        }

        static constexpr SelfType RightVector() noexcept {
            return SelfType{ 1, 0 };
        }

        static constexpr SelfType UpVector() noexcept {
            return SelfType{ 0, 1 };
        }

        static constexpr SelfType DownVector() noexcept {
            return SelfType{ 0, -1 };
        }

    public:
        constexpr BasicVec2() noexcept :
            x(0), y(0)
        {}

        constexpr explicit BasicVec2(ValueType scalar) noexcept :
            BasicVec2(scalar, scalar)
        {}

        constexpr BasicVec2(ValueType a, ValueType b) noexcept :
            x(a), y(b)
        {}

        constexpr BasicVec2(std::array<ValueType, 2> arr) noexcept :
            x(arr[0]), y(arr[1])
        {}

    public:
        constexpr SelfType& operator=(const SelfType& other) noexcept = default;
        constexpr SelfType& operator=(std::array<ValueType, 2> arr) noexcept {
            x = arr[0];
            y = arr[1];

            return *this;
        }

        constexpr bool operator==(const SelfType& other) const noexcept {
            return x == other.x && y == other.y;
        }

        constexpr bool operator!=(const SelfType& other) const noexcept {
            return !(*this == other);
        }

        constexpr SelfType operator+(const SelfType& other) const noexcept {
            return SelfType(x + other.x, y + other.y);
        }

        constexpr SelfType operator-(const SelfType& other) const noexcept {
            return SelfType(x - other.x, y - other.y);
        }

        constexpr SelfType operator-() const noexcept {
            return SelfType(-x, -y);
        }

        constexpr SelfType operator*(ValueType val) const noexcept {
            return SelfType(x * val, y * val);
        }

        constexpr SelfType operator*(const SelfType& other) const noexcept {
            return SelfType(x * other.x, y * other.y);
        }

        constexpr SelfType operator/(ValueType val) const noexcept {
            return SelfType(x / val, y / val);
        }

        constexpr SelfType operator/(const SelfType& other) const noexcept {
            return SelfType(x / other.x, y / other.y);
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
        constexpr std::array<ValueType, 2> ToArray() const noexcept {
            return { x, y };
        }

        constexpr float Magnitude() const noexcept {
            return std::sqrt(Numeric::pow2(x) + Numeric::pow2(y));
        }

        constexpr float Dot(const SelfType& other) const noexcept {
            return (x * other.x) + (y * other.y);
        }

        constexpr SelfType Cross(const SelfType& other) const noexcept {
            return *this * other;
        }

        constexpr ValueType ValuedDot(const SelfType& other) const noexcept {
            return BasicCast::To<ValueType>(Dot(other));
        }
    };


    using Vec2 = BasicVec2<f32>;
    using IVec2 = BasicVec2<i32>;
    using UVec2 = BasicVec2<u32>;
    using BVec2 = BasicVec2<bool>;
    using DVec2 = BasicVec2<f64>;
    using Point2D = Vec2;
}
