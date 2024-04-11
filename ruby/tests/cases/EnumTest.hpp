#pragma once

#include <utility/Enum.hpp>

namespace Ruby::Tests
{
    RUBY_ENUM(SomeEnum,
        ONE = 1 << 0,
        TWO = (1 << 1),
        THREE = (1 << 10),
        FOUR = ONE
    );
    
    class EnumTest
    {
    public:
        RUBY_ENUM_CLASS(InnerEnum,
            INNER_ONE,
            INNER_TWO,
            INNER_THREE = 5000,
            INNER_FOUR
        );

        RUBY_NODISCARD static bool Test()
        {
            auto&& reflector = EnumReflector::Create<SomeEnum>();
            auto&& innerReflector = EnumReflector::Create<InnerEnum>();

            if (reflector.GetName() != "SomeEnum" || innerReflector.GetName() != "InnerEnum")
                return false;

            if (reflector.GetByKey("THREE" ).GetValue() != (1 << 10) || innerReflector.At(1).GetValue() != 2)
                return false;

            if (reflector.Size() != 3)
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