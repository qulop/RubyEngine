#pragma once


#include <common/meta/Concepts.hpp>
#include <common/cast/Cast.hpp>
#include <common/Numeric.hpp>
#include <common/Debug.hpp>

#include <glm/vec4.hpp>


namespace Kiwi {
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

        constexpr BasicVec4(const glm::vec4& vec) noexcept :
            x(vec.x), y(vec.y), z(vec.z), w(vec.w)
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

        constexpr bool operator==(const glm::vec4& other) const noexcept {
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

        constexpr ValueType& operator[](size_t idx) noexcept {
            KIWI_ASSERT(idx < Size(), "index out of range");

            if (idx == 0) {
                return x;
            }
            else if (idx == 1) {
                return y;
            }
            else if (idx == 2) {
                return z;
            }
            else {
                return w;
            }
        }

        constexpr ValueType operator[](size_t idx) const noexcept {
            KIWI_ASSERT(idx < Size(), "index out of range");

            if (idx == 0) {
                return x;
            }
            else if (idx == 1) {
                return y;
            }
            else if (idx == 2) {
                return z;
            }
            else {
                return w;
            }
        }


    public:
        constexpr std::array<ValueType, 4> ToArray() const noexcept {
            return { x, y, z, w };
        }

        constexpr glm::vec4 ToGlmVec4() const noexcept {
            return { x, y, z, w };
        }

        KIWI_NODISCARD constexpr f32 Magnitude() const noexcept {
            return std::sqrt(Numeric::pow2(x) + Numeric::pow2(y) + Numeric::pow2(z) + Numeric::pow2(w));
        }

        constexpr f32 Dot(const SelfType& other) const noexcept {
            return (x * other.x) + (y * other.y) + (z * other.z) + (w * other.w);
        }

        constexpr SelfType GetNormalized() const noexcept {
            f32 m = Magnitude();
            return SelfType(x / m, y / m, z / m, w / m);
        }

        constexpr SelfType& NormalizeSelf() noexcept {
            *this = GetNormalized();
            return *this;
        }

        constexpr SelfType Cross(const SelfType& other) const noexcept {
            return *this * other;
        }
    };


    using Vec4 = BasicVec4<f32>;
    using I32Vec4 = BasicVec4<i32>;
    using U32Vec4 = BasicVec4<u32>;
    using BVec4 = BasicVec4<bool>;
    using DVec4 = BasicVec4<f64>;
    using Point4D = Vec4;
}
