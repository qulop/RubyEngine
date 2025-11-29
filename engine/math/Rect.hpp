#pragma once

#include <types/Concepts.hpp>
#include <math/vec/Vec2.hpp>



namespace Ruby {
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
        Rect() = default;

        Rect(ValueType x0, ValueType y0, ValueType x1, ValueType y1) :
            topLeft(x0, y0),
            bottomRight(x1, y1)
        {}

        Rect(const VectorType& topLeft, const VectorType& bottomRight) :
            topLeft(topLeft),
            bottomRight(bottomRight)
        {}

        Rect(const Rect& other) :
            topLeft(other.topLeft),
            bottomRight(other.bottomRight)
        {}

        Rect(Rect&& other) noexcept :
            topLeft(std::move(other.topLeft)),
            bottomRight(std::move(other.bottomRight))
        {}

    public:
        RUBY_NODISCARD bool IsInside(ValueType x, ValueType y) const {
            return topLeft.x <= x && x <= bottomRight.x && topLeft.y <= y && y <= bottomRight.y;
        }

        RUBY_NODISCARD VectorType Center() const {
            return VectorType(bottomRight.x * 0.5f, bottomRight.y * 0.5f);
        }

        RUBY_NODISCARD ValueType Width() const {
            return topLeft.x - bottomRight.x;
        }

        RUBY_NODISCARD ValueType Height() const {
            return topLeft.y - bottomRight.y;
        }

        RUBY_NODISCARD ValueType Area() const {
            return Width() * Height();
        }

        RUBY_NODISCARD VectorType MinimumCoordinate() const {
            return topLeft;
        }

        RUBY_NODISCARD VectorType MaximumCoordinate() const {
            return bottomRight;
        }


        RUBY_NODISCARD bool operator==(const Rect& other) const {
            return topLeft == other.topLeft && bottomRight == other.bottomRight;
        }

        RUBY_NODISCARD bool operator!=(const Rect& other) const {
            return !(*this == other);
        }

        Rect& operator=(const Rect& other) {
            topLeft = other.topLeft;
            bottomRight = other.bottomRight;

            return *this;
        }

        Rect& operator=(Rect&& other) noexcept {
            topLeft = std::move(other.topLeft);
            bottomRight = std::move(other.bottomRight);

            return *this;
        }
    };


    using FRect = Rect<f32>;
    using F64Rect = Rect<f64>;
    using IRect = Rect<i32>;
    using URect = Rect<u32>;
    using I64Rect = Rect<i64>;
}