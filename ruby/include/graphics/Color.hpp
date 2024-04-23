#pragma once

#include <utility/RubyUtility.hpp>
#include <utility/StdInc.hpp>
#include <glm/vec3.hpp>


namespace Ruby
{
    glm::vec3 fromHexToRGB(const RubyString& hex);


    class RUBY_API Color
    {
        using VectorType = glm::vec3;

    public:
        Color(const VectorType& color) :
            m_color(color)
        {}

        Color(const RubyString& hex) :
                m_color(fromHexToRGB(hex))
        {
            m_color.r /= 255;
            m_color.g /= 255;
            m_color.b /= 255;
        }

        Color(f32 r, f32 g, f32 b) :
            m_color(ClampValues(r, g, b))
        {}

        Color(i32 r, i32 g, i32 b) :
            m_color(ClampValues(r, g, b))
        {
            m_color.r /= 255;
            m_color.g /= 255;
            m_color.b /= 255;
        }


        RUBY_NODISCARD const VectorType& Get() const noexcept;
        RUBY_NODISCARD i32 Red() const noexcept;
        RUBY_NODISCARD i32 Green() const noexcept;
        RUBY_NODISCARD i32 Blue() const noexcept;

    private:
        template<typename Tx>
        constexpr VectorType ClampValues(Tx r, Tx g, Tx b) const noexcept
        {
            Tx min = (std::is_floating_point_v<std::decay_t<Tx>>) ? 0.0f : 0;
            Tx max = (std::is_floating_point_v<std::decay_t<Tx>>) ? 1.0f : 255;

            return { std::clamp(r, min, max),
                     std::clamp(g, min, max),
                     std::clamp(b, min, max) };
        }

        RUBY_NODISCARD constexpr i32 ToBytes(f32 value) const noexcept
        { return static_cast<i32>(255 * value); }


    private:
        VectorType m_color;
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