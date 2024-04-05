#pragma once

#include <utility/Enum.hpp>

namespace Ruby::Tests
{
    RUBY_ENUM(SomeEnum,
        ONE = 10,
        TWO,
        THREE = 1000,
        FOUR    
    )
    
    class EnumTest
    {
    public:
        RUBY_NODISCARD static bool Test(void)
        {
            auto&& relfector = EnumReflector::Create<SomeEnum>();
            

            return true;
        }
    };
}