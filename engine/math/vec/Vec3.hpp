#pragma once


#include <types/Concepts.hpp>
#include "types/cast/Cast.hpp"

#include <utility/Numeric.hpp>


namespace Ruby {
    template<Concepts::Number T>
    class BasicVec3 {
    public:
        using SelfType = BasicVec3;

        using value_type = T;
        using ValueType = T;

    public:
        union {
            struct { ValueType x, y, z; };
            struct { ValueType r, g, b; };
            struct { ValueType s, t, p; };
        };

    public:
        static constexpr size_t Size() noexcept {
            return 3;
        }

        static constexpr SelfType ZeroVector() noexcept {
            return SelfType{ 0 };
        }

        static constexpr SelfType LeftVector() noexcept {
            return SelfType{ -1, 0, 0 };
        }

        static constexpr SelfType RightVector() noexcept {
            return SelfType{ 1, 0, 0 };
        }

        static constexpr SelfType UpVector() noexcept {
            return SelfType{ 0, 1, 0 };
        }

        static constexpr SelfType DownVector() noexcept {
            return SelfType{ 0, -1, 0 };
        }


    public:
        constexpr BasicVec3() noexcept :
            x(0), y(0), z(0)
        {}

        constexpr explicit BasicVec3(ValueType scalar) noexcept :
            BasicVec3(scalar, scalar, scalar)
        {}

        constexpr BasicVec3(ValueType a, ValueType b, ValueType c) noexcept :
            x(a), y(b), z(c)
        {}

        constexpr BasicVec3(std::array<ValueType, 3> arr) noexcept :
            x(arr[0]), y(arr[1]), z(arr[2])
        {}

        constexpr BasicVec3(const glm::vec3& vec) noexcept :
            x(vec.x), y(vec.y), z(vec.z)
        {}

    public:
        constexpr BasicVec3& operator=(const BasicVec3& other) noexcept = default;
        constexpr BasicVec3& operator=(std::array<ValueType, 3> arr) noexcept {
            x = arr[0];
            y = arr[1];
            y = arr[2];

            return *this;
        }

        constexpr bool operator==(const SelfType& other) const noexcept {
            return x == other.x && y == other.y && z == other.z;
        }

        constexpr bool operator!=(const SelfType& other) const noexcept {
            return !(*this == other);
        }

        constexpr SelfType operator+(const SelfType& other) const noexcept {
            return SelfType(x + other.x, y + other.y, z + other.z);
        }

        constexpr SelfType operator-(const SelfType& other) const noexcept {
            return SelfType(x - other.x, y - other.y, z - other.z);
        }

        constexpr SelfType operator-() const noexcept {
            return SelfType(-x, -y, -z);
        }

        constexpr SelfType operator*(ValueType val) const noexcept {
            return SelfType(x * val, y * val, z * val);
        }

        constexpr SelfType operator*(const SelfType& other) const noexcept {
            return SelfType(x * other.x, y * other.y, z * other.z);
        }

        constexpr SelfType operator/(ValueType val) const noexcept {
            return SelfType(x / val, y / val, z / val);
        }

        constexpr SelfType operator/(const SelfType& other) const noexcept {
            return SelfType(x / other.x, y / other.y, z / other.z);
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

        constexpr ValueType& operator[](size_t idx) noexcept {
            RUBY_ASSERT(idx < Size(), "index out of range");

            switch (idx) {
                case 0: return x;
                case 1: return y;
                case 2: return z;
            }
        }

        constexpr ValueType operator[](size_t idx) const noexcept {
            RUBY_ASSERT(idx < Size(), "index out of range");

            switch (idx) {
                case 0: return x;
                case 1: return y;
                case 2: return z;
            }
        }

    public:
        constexpr std::array<ValueType, 3> ToArray() const noexcept {
            return { x, y, z };
        }

        constexpr glm::vec3 ToGlmVec3() const noexcept {
            return { x, y, z };
        }

        RUBY_NODISCARD constexpr f32 Magnitude() const noexcept {
            return std::sqrt(Numeric::pow2(x) + Numeric::pow2(y) + Numeric::pow2(z));
        }

        constexpr f32 Dot(const SelfType& other) const noexcept {
            return (x * other.x) + (y * other.y) + (z * other.z);
        }

        constexpr SelfType GetNormalized() const noexcept {
            f32 m = Magnitude();
            return SelfType(x / m, y / m, z / m);
        }

        constexpr SelfType& NormalizeSelf() noexcept {
            *this = GetNormalized();
            return *this;
        }

        constexpr SelfType Cross(const SelfType& other) const noexcept {
            return SelfType(
                y * other.z - z * other.y,
                z * other.x - x * other.z,
                x * other.y - y * other.x
            );
        }
    };


    template<Concepts::Number T>
    constexpr BasicVec3<T> Cross(const BasicVec3<T>& lhs, const BasicVec3<T>& rhs) noexcept {
        return lhs.Cross(rhs);
    }


    using Vec3 = BasicVec3<f32>;
    using IVec3 = BasicVec3<i32>;
    using UVec3 = BasicVec3<u32>;
    using BVec3 = BasicVec3<bool>;
    using DVec3 = BasicVec3<f64>;
    using Point3D = Vec3;
}
