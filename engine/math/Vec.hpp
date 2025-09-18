#pragma once

#include <types/TypeTraits.hpp>
#include <types/Concepts.hpp>
#include <types/Cast.hpp>
#include <utility/Numeric.hpp>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include "Trigonometric.hpp"


namespace Ruby::Math::Details::Vector {
    template<typename Tx, size_t N>
        requires (std::is_arithmetic_v<Tx>&& N <= 4)
    class VecBase {
    public:
        using value_type = Tx;
        using ValueType = Tx;

    public:
        RUBY_NODISCARD constexpr size_t Size() const {
            return N;
        }

    protected:
        constexpr VecBase() = default;


        template<typename Derived>
            requires Ruby::Concepts::ImplementsEqualityOp<Derived>
        static constexpr bool NEQ(const Derived& self, Derived&& other) {
            return !(self == other);
        }

        template<typename... Args>
            requires
        (sizeof...(Args) > 0 && sizeof...(Args) <= 4) &&
            (std::conjunction_v<std::is_same<Args, Tx>...>)
            static constexpr auto GetMagnitude_Base(Args&&... args) {
            return std::sqrt(Numeric::accumulateVariadic(Numeric::pow2(args)...));
        }

        template<typename VecType, typename... Args>
        static constexpr VecType GetNormalized_Base(Args&&... args) {
            constexpr auto magnitude = GetMagnitude_Base(std::forward<Args>(args)...);

            return VecType((args / magnitude)...);
        }
    };

}


namespace Ruby::Math {
    // Aliases for glm vectors
    template<typename Tx>
    using GlmVec2 = glm::vec<2, Tx, glm::defaultp>;

    template<typename Tx>
    using GlmVec3 = glm::vec<3, Tx, glm::defaultp>;

    template<typename Tx>
    using GlmVec4 = glm::vec<4, Tx, glm::defaultp>;
    // ----------------


    template<typename Tx>
    class BasicVec2 : public Details::Vector::VecBase<Tx, 2> {
    protected:
        using MyVecBase = Details::Vector::VecBase<Tx, 2>;
        using ValueType = typename MyVecBase::ValueType;

    public:
        using Self = BasicVec2;

        union {
            struct { ValueType x, y; };
            struct { ValueType s, t; };
            struct { ValueType r, g; };
        };

        constexpr BasicVec2() {
            setVariadic(cast<ValueType>(0), x, y);
        }

        constexpr BasicVec2(ValueType x, ValueType y) :
            x(x), y(y) {}

        constexpr BasicVec2(ValueType n) { // NOLINT
            setVariadic(n, x, y);
        }

        explicit constexpr BasicVec2(const GlmVec2<ValueType>& glmVec) :
            x(glmVec.x), y(glmVec.y) {}

        constexpr BasicVec2(const Self& other) {
            *this = other;
        }

        constexpr BasicVec2(Self&& other) noexcept {
            *this = std::move(other);
        }


        constexpr auto GetMagnitude() const {
            return MyVecBase::GetMagnitude_Base(x, y);
        }

        constexpr Self GetNormalized() const {
            return MyVecBase::template GetNormalized_Base<Self>(x, y);
        }

        constexpr Self& NormalizeSelf() {
            *this = GetNormalized();
            return *this;
        };

        Self& operator=(Self&& other) noexcept {
            x = std::exchange(other.x, cast<ValueType>(0));
            y = std::exchange(other.y, cast<ValueType>(0));

            return *this;
        }

        Self& operator=(const Self& other) {
            x = other.x, y = other.y;

            return *this;
        }

        constexpr bool operator==(const Self& other) const {
            return (x == other.x) && (y == other.y);
        }

        constexpr bool operator!=(const Self& other) const {
            return MyVecBase::NEQ(*this, other);
        }
    };


    template<typename Tx>
    class BasicVec3 : public Details::Vector::VecBase<Tx, 3> {
    protected:
        using MyVecBase = Details::Vector::VecBase<Tx, 3>;
        using ValueType = typename MyVecBase::ValueType;

    public:
        using Self = BasicVec3<Tx>;

        union {
            struct { ValueType x, y, z; };
            struct { ValueType s, t, p; };
            struct { ValueType r, g, b; };
        };


        constexpr BasicVec3() {
            setVariadic(0, x, y, z);
        }

        constexpr BasicVec3(ValueType x, ValueType y, ValueType z) :
            x(x), y(y), z(z) {}

        constexpr BasicVec3(ValueType n) {   // NOLINT
            setVariadic(n, x, y, z);
        }

        explicit constexpr BasicVec3(const GlmVec3<ValueType>& glmVec) :
            x(glmVec.x), y(glmVec.y), z(glmVec.z) {}

        constexpr BasicVec3(const Self& other) {
            *this = other;
        }

        constexpr BasicVec3(Self&& other) noexcept {
            *this = std::move(other);
        }


        constexpr ValueType GetMagnitude() const {
            return MyVecBase::GetMagnitude_Base(x, y, z);
        }

        constexpr Self GetNormalized() const {
            return MyVecBase::template GetNormalized_Base<Self>(x, y, z);
        }


        Self& operator=(Self&& other) noexcept {
            x = std::exchange(other.x, cast<ValueType>(0));
            y = std::exchange(other.y, cast<ValueType>(0));
            z = std::exchange(other.z, cast<ValueType>(0));

            return *this;
        }

        Self& operator=(const Self& other) {
            x = other.x, y = other.y, z = other.z;

            return *this;
        }

        constexpr bool operator==(const Self& other) const {
            return (x == other.x) && (y == other.y) && (z == other.z);
        }

        constexpr bool operator!=(const Self& other) const {
            return MyVecBase::NEQ(*this, other);
        }
    };


    template<typename Tx>
    class BasicVec4 : public Details::Vector::VecBase<Tx, 4> {
    protected:
        using MyVecBase = Details::Vector::VecBase<Tx, 4>;
        using ValueType = typename MyVecBase::ValueType;

    public:
        using Self = BasicVec4<Tx>;

        union {
            struct { ValueType x, y, z, w; };
            struct { ValueType s, t, p, q; };
            struct { ValueType r, g, b, a; };
        };


        constexpr BasicVec4() {
            setVariadic(cast<ValueType>(0), x, y, z, w);
        }

        constexpr BasicVec4(ValueType x, ValueType y, ValueType z, ValueType w) :
            x(x), y(y), z(z), w(w) {}

        constexpr BasicVec4(ValueType n) {   // NOLINT
            setVariadic(n, x, y, z, w);
        }

        explicit constexpr BasicVec4(const GlmVec4<ValueType>& glmVec) :
            x(glmVec.x), y(glmVec.y), z(glmVec.z), w(glmVec.w) {}

        constexpr BasicVec4(const Self& other) {
            *this = other;
        }

        constexpr BasicVec4(Self&& other) noexcept {
            *this = std::move(other);
        }


        constexpr ValueType GetMagnitude() const {
            return MyVecBase::GetMagnitude_Base(x, y, z, w);
        }

        constexpr Self GetNormalized() const {
            return MyVecBase::template GetNormalized_Base<Self>(x, y, z, w);
        }


        Self& operator=(Self&& other) noexcept {
            x = std::exchange(other.x, BasicCast::To<ValueType>(0));
            y = std::exchange(other.y, BasicCast::To<ValueType>(0));
            z = std::exchange(other.z, BasicCast::To<ValueType>(0));
            w = std::exchange(other.w, BasicCast::To<ValueType>(0));

            return *this;
        }

        Self& operator=(const Self& other) {
            x = other.x, y = other.y;
            z = other.z, w = other.w;

            return *this;
        }

        constexpr bool operator==(const Self& other) const {
            return (x == other.x) && (y == other.y) &&
                (z == other.z) && (w == other.w);
        }

        constexpr bool operator!=(const Self& other) const {
            return MyVecBase::NEQ(*this, other);
        }
    };
}


namespace Ruby::Math {
    template<typename Tx>
        requires requires (Tx vec) {
            { vec.GetMagnitude() } -> std::convertible_to<typename Tx::ValueType>;
        }
    auto magnitude(const Tx& vec) -> typename Tx::ValueType {
        return vec.GetMagnitude();
    }

    template<typename Tx>
        requires requires (Tx vec) {
            { vec.GetNormalized() } -> std::convertible_to<Tx>;
        }
    auto normalize(const Tx& vec) -> Tx {
        return vec.GetNormalized();
    }


    using Vec2  = BasicVec2<f32>;
    using IVec2 = BasicVec2<i32>;
    using UVec2 = BasicVec2<u32>;
    using BVec2 = BasicVec2<bool>;
    using DVec2 = BasicVec2<f64>;
    using Point2D = Vec2;

    using Vec3  = BasicVec3<f32>;
    using IVec3 = BasicVec3<i32>;
    using UVec3 = BasicVec3<u32>;
    using BVec3 = BasicVec3<bool>;
    using DVec3 = BasicVec3<f64>;
    using Point3D = Vec3;

    using Vec4  = BasicVec4<f32>;
    using IVec4 = BasicVec4<i32>;
    using UVec4 = BasicVec4<u32>;
    using BVec4 = BasicVec4<bool>;
    using DVec4 = BasicVec4<f64>;
}
