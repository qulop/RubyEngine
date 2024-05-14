#include <graphics/Color.hpp>


namespace Ruby
{
    glm::vec4 fromHexToRGB(const RubyString& hex)
    {
        RUBY_ASSERT(hex.front() == '#' && hex.size() == 7, "Incorrect string format!");

        i32 r = 0, g = 0, b = 0;
        sscanf_s(hex.c_str(), "#%02x%02x%02x", &r, &g, &b);

        return { r, g, b, 1 };
    }

    const Color::VectorType& Color::Get() const noexcept
    { return m_color; }

    i32 Color::Red() const noexcept
    { return ToBytes(m_color.r); }

    i32 Color::Green() const noexcept
    { return ToBytes(m_color.g); }

    i32 Color::Blue() const noexcept
    { return ToBytes(m_color.b); }

    i32 Color::Alpha() const noexcept
    { return ToBytes(m_color.a); }
}