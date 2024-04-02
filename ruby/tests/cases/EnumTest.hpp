#pragma once

#include <utility/Enum.hpp>

namespace Ruby::Tests
{
    RUBY_ENUM(EventType,
    MOUSE_MOVED,
    MOUSE_PRESSED = 10,
    SOME_ANOTHER_EVENT
    );
    
    class EnumTest
    {
    public:
        RUBY_NODISCARD static bool Test(void)
        {
            auto&& reflector = EnumReflector::CreateReflector(EventType);

            return true;
        }
    };
}