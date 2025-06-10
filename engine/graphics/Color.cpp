#include "Color.hpp"

#include <utility/Assert.hpp>
#include <platform/Platform.hpp>


namespace Ruby {
    glm::vec4 fromHexToRGB(const String& hex) {
        RUBY_ASSERT(hex.front() == '#' && hex.size() == 7, "Incorrect string format!");

        i32 r = 0, g = 0, b = 0;
        sscanf_s(hex.c_str(), "#%02x%02x%02x", &r, &g, &b);

        return { r, g, b, 1 };
    }

    const Color::VecType& Color::Get() const noexcept {
        return m_color;
    }

    f32 Color::Red() const noexcept {
        return m_color.r;
    }

    f32 Color::Green() const noexcept {
        return m_color.g;
    }

    f32 Color::Blue() const noexcept {
        return m_color.b;
    }

    f32 Color::Alpha() const noexcept {
        return m_color.a;
    }

    Math::IVec4 Color::AsBytes() const noexcept {
        return {
            RedAsBytes(), GreenAsBytes(),
            BlueAsBytes(), AlphaAsBytes()
        };
    }

    i32 Color::RedAsBytes() const noexcept {
        return ToBytes(m_color.r);
    }

    i32 Color::GreenAsBytes() const noexcept {
        return ToBytes(m_color.g);
    }

    i32 Color::BlueAsBytes() const noexcept {
        return ToBytes(m_color.b);
    }

    i32 Color::AlphaAsBytes() const noexcept {
        return ToBytes(m_color.a);
    }
}