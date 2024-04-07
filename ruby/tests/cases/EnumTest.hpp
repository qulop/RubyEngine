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
        RUBY_ENUM_CLASS(InnerEnum,
            INNER_ONE,
            INNER_TWO,
            INNER_THREE = 5000,
            INNER_FOUR
        );

        RUBY_NODISCARD static bool Test(void)
        {
            auto&& reflector = EnumReflector::Create<SomeEnum>();
            auto&& innerReflector = EnumReflector::Create<InnerEnum>();

            if (reflector.GetName() != "SomeEnum" || innerReflector.GetName() != "InnerEnum")
                return false;

            if (innerReflector.At(0).GetValue() != 1)
                return false;

            if (reflector.GetByKey("FOUR" ).GetValue() != 1001)
                return false;

            if (reflector.Size() != 4)
                return false;

            auto&& outerIt = reflector.begin();
            for (i32 i = 0; outerIt != reflector.end(); i++, outerIt++)
                if (*outerIt != reflector.At(i))
                    return false;

            auto&& innerIt = reflector.begin();
            for (i32 i = 0; innerIt != reflector.end(); i++, innerIt++)
                if (*innerIt != reflector.At(i))
                    return false;

            return true;
        }
    };
}