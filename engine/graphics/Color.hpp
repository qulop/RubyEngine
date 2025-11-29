#pragma once

#include <types/Concepts.hpp>
#include <types/StdInc.hpp>

#include <utility/Definitions.hpp>
#include <utility/Assert.hpp>

#include <math/vec/Vec4.hpp>


namespace Ruby::Details::Globals {
    constexpr size_t HEX_STRING_SIZE = 7;   // 6 symbols for colors(RGB) and 1 for '#' sign
}

namespace Ruby::Details::Color {
    constexpr i32 HexCharToI32(char c) {
        RUBY_ASSERT((c >= '0' && c <= '9') ||
                    (c >= 'a' && c <= 'f') ||
                    (c >= 'A' && c <= 'F'),
                    "Incorrect hex digit"
        );

        if (c >= '0' && c <= '9') {
            return (c - '0');
        }

        return ((c >= 'a' && c <= 'f') ? (c - 'a') : (c - 'A')) + 10;
    }

    constexpr byte HexPairIntoByte(char first, char second) {
        return BasicCast::To<byte>((HexCharToI32(first) << 4) + HexCharToI32(second));
    }
}



namespace Ruby {
    class RUBY_API Color {
        using VecType = Vec4;
        using BytesTupleType = std::tuple<i32, i32, i32, i32>;
        using TupleType = std::tuple<f32, f32, f32, f32>;

    public:
        RUBY_NODISCARD static constexpr Color::VecType FromHexToRGB(std::string_view hex) {
            RUBY_ASSERT(hex.front() == '#' && hex.size() == Details::Globals::HEX_STRING_SIZE,
                "Incorrect hex string format!"
            );

            using ValueType = VecType::value_type;
            return {
                BasicCast::To<ValueType>(Details::Color::HexPairIntoByte(hex.at(1), hex.at(2)) / 255.f),
                BasicCast::To<ValueType>(Details::Color::HexPairIntoByte(hex.at(3), hex.at(4)) / 255.f),
                BasicCast::To<ValueType>(Details::Color::HexPairIntoByte(hex.at(5), hex.at(6)) / 255.f),
                BasicCast::To<ValueType>(1)
            };
        }

        template<Concepts::Number Tx>
        static constexpr Tx GetMaxNumericValueForType() noexcept {
            if constexpr (std::is_floating_point_v<std::decay_t<Tx>>) {
                return BasicCast::To<Tx>(1);
            }

            return BasicCast::To<Tx>(255);
        }

    public:
        explicit constexpr Color(VecType color) :
            m_color(std::move(color)) 
        {}

        constexpr Color(std::string_view hex) : // NOLINT
            m_color(FromHexToRGB(hex)) 
        {
            m_color.r /= 255;
            m_color.g /= 255;
            m_color.b /= 255;
            m_color.a /= 255;
        }

        constexpr Color(f32 r, f32 g, f32 b, f32 a = 1.0f) :
            m_color(ClampColorValues(r, g, b, a)) 
        {}

        constexpr Color(i32 r, i32 g, i32 b, i32 a = 1) :
            m_color(ClampColorValues(BasicCast::To<f32>(r), BasicCast::To<f32>(g),
                    BasicCast::To<f32>(b), BasicCast::To<f32>(a))) 
        {
            m_color.r /= 255;
            m_color.g /= 255;
            m_color.b /= 255;
            m_color.a /= 255;
        }


        RUBY_NODISCARD constexpr VecType& Get() noexcept {
            return m_color;
        }

        RUBY_NODISCARD constexpr TupleType GetTuple() const noexcept {
            return std::make_tuple(m_color.r, m_color.g, m_color.b, m_color.a);
        }

        RUBY_NODISCARD constexpr f32 Red() const noexcept {
            return m_color.r;
        }

        RUBY_NODISCARD constexpr f32 Green() const noexcept {
            return m_color.g;
        }

        RUBY_NODISCARD constexpr f32 Blue() const noexcept {
            return m_color.b;
        }

        RUBY_NODISCARD constexpr f32 Alpha() const noexcept {
            return m_color.a;
        }

        RUBY_NODISCARD constexpr IVec4 AsBytes() const noexcept {
            return { RedAsBytes(), GreenAsBytes(), BlueAsBytes(), AlphaAsBytes() };
        }

        RUBY_NODISCARD constexpr BytesTupleType AsBytesTuple() const noexcept {
            return std::make_tuple(RedAsBytes(), GreenAsBytes(), BlueAsBytes(), AlphaAsBytes());
        }

        RUBY_NODISCARD constexpr i32 RedAsBytes() const noexcept {
            return FloatColorValueToByte(m_color.r);
        }

        RUBY_NODISCARD constexpr i32 GreenAsBytes() const noexcept {
            return FloatColorValueToByte(m_color.g);
        }

        RUBY_NODISCARD constexpr i32 BlueAsBytes() const noexcept {
            return FloatColorValueToByte(m_color.b);
        }

        RUBY_NODISCARD constexpr i32 AlphaAsBytes() const noexcept {
            return FloatColorValueToByte(m_color.a);
        }

    private:
        template<typename Tx>
        RUBY_NODISCARD constexpr VecType ClampColorValues(Tx r, Tx g, Tx b, Tx a) const noexcept {
            auto min = static_cast<Tx>(0);
            auto max = GetMaxNumericValueForType<Tx>();

            return VecType(std::clamp(r, min, max),
                           std::clamp(g, min, max),
                           std::clamp(b, min, max),
                           std::clamp(a, min, max));
        }

        RUBY_NODISCARD constexpr i32 FloatColorValueToByte(f32 value) const noexcept {
            return BasicCast::To<i32>(255 * value);
        }


    private:
        VecType m_color;
    };


    constexpr Color COLOR_RED = { 1.0f, 0.0f, 0.0f };
    constexpr Color COLOR_GREEN = { 0.0f, 1.0f, 0.0f };
    constexpr Color COLOR_BLUE = { 0.0f, 0.0f, 1.0f };
    constexpr Color COLOR_WHITE = { 1.0f, 1.0f, 1.0f };
    constexpr Color COLOR_BLACK = { 0.0f, 0.0f, 0.0f };
    constexpr Color COLOR_YELLOW = { 1.0f, 1.0f, 0.0f };
    constexpr Color COLOR_CYAN = { 0.0f, 1.0f, 1.0f };
    constexpr Color COLOR_MAGENTA = { 1.0f, 0.0f, 1.0f };
    constexpr Color COLOR_ORANGE = { 1.0f, 0.5f, 0.0f };
    constexpr Color COLOR_PINK = { 1.0f, 0.0f, 0.5f };
    constexpr Color COLOR_PURPLE = { 0.5f, 0.0f, 0.5f };
    constexpr Color COLOR_BROWN = { 0.6f, 0.3f, 0.0f };
    constexpr Color COLOR_GRAY = { 0.5f, 0.5f, 0.5f };
    constexpr Color COLOR_DARK_GREEN = { 0.0f, 0.5f, 0.0f };
    constexpr Color COLOR_LIGHT_BLUE = { 0.5f, 0.5f, 1.0f };
    constexpr Color COLOR_NAVY_BLUE = { 0.0f, 0.0f, 0.5f };
}

