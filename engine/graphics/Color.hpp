#pragma once

#include <types/StdInc.hpp>
#include <glm/vec4.hpp>
#include <math/Vec.hpp>


namespace Ruby {
    namespace Details::Graphics {
        glm::vec4 fromHexToRGB(const String& hex);

        template<typename Tx>
        static constexpr Tx getMaxValueForColor() noexcept {
            if (std::is_floating_point_v<std::decay_t<Tx>>)
                return 1;
            return 255;
        }
    }




    class RUBY_API Color {
        using VecType = Math::Vec4;

    public:
        explicit Color(VecType color) :
            m_color(std::move(color))
        {}

        Color(const String& hex) : // NOLINT
                m_color(Details::Graphics::fromHexToRGB(hex))
        {
            m_color.r /= 255;
            m_color.g /= 255;
            m_color.b /= 255;
            m_color.a /= 255;
        }

        Color(f32 r, f32 g, f32 b, f32 a = 1.0f) :
            m_color(ClampColorValues(r, g, b, a))
        {}

        Color(i32 r, i32 g, i32 b, i32 a = 1) :
            m_color(ClampColorValues(cast<f32>(r), cast<f32>(g),
                    cast<f32>(b), cast<f32>(a)))
        {
            m_color.r /= 255;
            m_color.g /= 255;
            m_color.b /= 255;
            m_color.a /= 255;
        }


        RUBY_NODISCARD const VecType& Get() const noexcept;

        RUBY_NODISCARD f32 Red() const noexcept;
        RUBY_NODISCARD f32 Green() const noexcept;
        RUBY_NODISCARD f32 Blue() const noexcept;
        RUBY_NODISCARD f32 Alpha() const noexcept;

        RUBY_NODISCARD Math::IVec4 AsBytes() const noexcept;
        RUBY_NODISCARD i32 RedAsBytes() const noexcept;
        RUBY_NODISCARD i32 GreenAsBytes() const noexcept;
        RUBY_NODISCARD i32 BlueAsBytes() const noexcept;
        RUBY_NODISCARD i32 AlphaAsBytes() const noexcept;

    private:
        template<typename Tx>
        RUBY_NODISCARD constexpr VecType ClampColorValues(Tx r, Tx g, Tx b, Tx a) const noexcept {
            Tx min = 0;
            Tx max = Details::Graphics::getMaxValueForColor<Tx>();

            return VecType(std::clamp(r, min, max),
                     std::clamp(g, min, max),
                     std::clamp(b, min, max),
                     std::clamp(a, min, max) );
        }

        RUBY_NODISCARD constexpr i32 ToBytes(f32 value) const noexcept { // NOLINT
            return static_cast<i32>(255 * value);
        }


    private:
        VecType m_color;
    };


    const Color COLOR_RED = { 1.0f, 0.0f, 0.0f };
    const Color COLOR_GREEN = { 0.0f, 1.0f, 0.0f };
    const Color COLOR_BLUE = { 0.0f, 0.0f, 1.0f };
    const Color COLOR_WHITE = { 1.0f, 1.0f, 1.0f };
    const Color COLOR_BLACK = { 0.0f, 0.0f, 0.0f };
    const Color COLOR_YELLOW = { 1.0f, 1.0f, 0.0f };
    const Color COLOR_CYAN = { 0.0f, 1.0f, 1.0f };
    const Color COLOR_MAGENTA = { 1.0f, 0.0f, 1.0f };
    const Color COLOR_ORANGE = { 1.0f, 0.5f, 0.0f };
    const Color COLOR_PINK = { 1.0f, 0.0f, 0.5f };
    const Color COLOR_PURPLE = { 0.5f, 0.0f, 0.5f };
    const Color COLOR_BROWN = { 0.6f, 0.3f, 0.0f };
    const Color COLOR_GRAY = { 0.5f, 0.5f, 0.5f };
    const Color COLOR_DARK_GREEN = { 0.0f, 0.5f, 0.0f };
    const Color COLOR_LIGHT_BLUE = { 0.5f, 0.5f, 1.0f };
    const Color COLOR_NAVY_BLUE = { 0.0f, 0.0f, 0.5f };
} 