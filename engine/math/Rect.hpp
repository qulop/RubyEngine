#pragma once

#include <common/Concepts.hpp>
#include <math/vec/Vec2.hpp>



namespace Kiwi {
    /*
     The rectangle structure. Here is how `topLeft` and `bottomRight` variables maps on the screen rectangle like this:

     `topLeft` - the minimum coordinate of the rectangle
       V
       +-------------+
       |             |
       |             |
       +-------------+
                     ^
                `bottomRight` - the maximum coordinate of the rectangle
    */
    template<Concepts::Number T>
    struct Rect {
    public:
        using SelfType = Rect;
        using VectorType = BasicVec2<T>;

        using value_type = T;
        using ValueType = T;

    public:
        VectorType topLeft;
        VectorType bottomRight;

    public:
        constexpr Rect() = default;

        constexpr Rect(ValueType x0, ValueType y0, ValueType x1, ValueType y1) :
            topLeft(x0, y0),
            bottomRight(x1, y1)
        {}

        constexpr Rect(const VectorType& topLeft, const VectorType& bottomRight) :
            topLeft(topLeft),
            bottomRight(bottomRight)
        {}

        constexpr Rect(const Rect& other) :
            topLeft(other.topLeft),
            bottomRight(other.bottomRight)
        {}

        constexpr Rect(Rect&& other) noexcept :
            topLeft(std::move(other.topLeft)),
            bottomRight(std::move(other.bottomRight))
        {}

    public:
        KIWI_NODISCARD constexpr bool IsInside(ValueType x, ValueType y) const {
            return topLeft.x <= x && x <= bottomRight.x && topLeft.y <= y && y <= bottomRight.y;
        }

        KIWI_NODISCARD constexpr VectorType Center() const {
            return VectorType(bottomRight.x * 0.5f, bottomRight.y * 0.5f);
        }

        KIWI_NODISCARD constexpr ValueType Width() const {
            return topLeft.x - bottomRight.x;
        }

        KIWI_NODISCARD constexpr ValueType Height() const {
            return topLeft.y - bottomRight.y;
        }

        KIWI_NODISCARD constexpr ValueType Area() const {
            return Width() * Height();
        }

        KIWI_NODISCARD constexpr VectorType MinimumCoordinate() const {
            return topLeft;
        }

        KIWI_NODISCARD constexpr VectorType MaximumCoordinate() const {
            return bottomRight;
        }


        KIWI_NODISCARD constexpr bool operator==(const Rect& other) const {
            return topLeft == other.topLeft && bottomRight == other.bottomRight;
        }

        KIWI_NODISCARD constexpr bool operator!=(const Rect& other) const {
            return !(*this == other);
        }

        constexpr Rect& operator=(const Rect& other) {
            topLeft = other.topLeft;
            bottomRight = other.bottomRight;

            return *this;
        }

        constexpr Rect& operator=(Rect&& other) noexcept {
            topLeft = std::move(other.topLeft);
            bottomRight = std::move(other.bottomRight);

            return *this;
        }
    };


    using FRect = Rect<f32>;
    using F64Rect = Rect<f64>;
    using U32Rect = Rect<u32>;
    using I32Rect = Rect<i32>;
    using I64Rect = Rect<i64>;
}