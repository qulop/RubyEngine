#pragma once

#include <glad/glad.h>
#include <utility/TypeTraits.hpp>

namespace Ruby
{
    struct RUBY_API Glyph
    {
        u32 textureID;

        u32 width;
        u32 height;    

        u32 bearingX;
        u32 bearingY;
        
        u32 advance;
    };
}
