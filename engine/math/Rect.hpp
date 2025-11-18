#pragma once

#include <types/Concepts.hpp>
#include <math/vec/Vec2.hpp>



namespace Ruby {
    template<Concepts::Number T>
    struct Rect {
    public:
        using SelfType = Rect;
        using VectorType = BasicVec2<T>;

        using value_type = T;
        using ValueType = T;

    public:
        VectorType bottomLeft;
        VectorType topRight;

    public:
        Rect() = default;

        Rect(ValueType x0, ValueType y0, ValueType x1, ValueType y1) :
            bottomLeft(x0, y0),
            topRight(x1, y1)
        {}

        Rect(const VectorType& bottomLeft, const VectorType& topRight) :
            bottomLeft(bottomLeft),
            topRight(topRight)
        {}

        Rect(const Rect& other) :
            bottomLeft(other.bottomLeft),
            topRight(other.topRight)
        {}

        Rect(Rect&& other) noexcept :
            bottomLeft(std::move(other.bottomLeft)),
            topRight(std::move(other.topRight))
        {}

    public:
        RUBY_NODISCARD bool IsInside(ValueType x, ValueType y) const {
            return bottomLeft.x <= x && x <= topRight.x && bottomLeft.y <= y && y <= topRight.y;
        }

        RUBY_NODISCARD VectorType Center() const {
            return VectorType(topRight.x * 0.5f, topRight.y * 0.5f);
        }

        RUBY_NODISCARD ValueType Width() const {
            return topRight.x - bottomLeft.x;
        }

        RUBY_NODISCARD ValueType Height() const {
            return topRight.y - bottomLeft.y;
        }

        RUBY_NODISCARD ValueType Area() const {
            return Width() * Height();
        }


        RUBY_NODISCARD bool operator==(const Rect& other) const {
            return bottomLeft == other.bottomLeft && topRight == other.topRight;
        }

        RUBY_NODISCARD bool operator!=(const Rect& other) const {
            return !(*this == other);
        }

        RUBY_NODISCARD Rect& operator=(const Rect& other) {
            bottomLeft = other.bottomLeft;
            topRight = other.topRight;

            return *this;
        }

        RUBY_NODISCARD Rect& operator=(Rect&& other) noexcept {
            bottomLeft = std::move(other.bottomLeft);
            topRight = std::move(other.topRight);

            return *this;
        }
    };


    using FRect = Rect<f32>;
    using F64Rect = Rect<f64>;
    using IRect = Rect<i32>;
    using URect = Rect<u32>;
    using I64Rect = Rect<i64>;
}