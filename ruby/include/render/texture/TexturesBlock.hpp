#pragma once

#include "Texture2D.hpp"

#include <type_trait.hpp>
#include <vector>

namespace Ruby
{
    template<typename... Args>
        requires std::conjunction_v<std::is_same<Args, Texture2D>...>
    class TextureBlock
    {
    public:
        TextureBlock(Args&&... texutes);

    };
}
