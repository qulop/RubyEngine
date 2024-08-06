#pragma once

#include <utility/Enum.hpp>


namespace Ruby::Tests {
    namespace Details::Enum {
        constexpr i32 thirdFieldValue = (1 << 10);

        RUBY_ENUM(SomeEnum,
            ONE = 1 << 0,
            TWO = (1 << 1),
            THREE = thirdFieldValue,
            FOUR = ONE
        );
    }


    class EnumTest {
    public:
        RUBY_ENUM_INNER(InnerEnum,
            INNER_ONE,
            INNER_TWO = 5000
        );

        RUBY_NODISCARD static bool Test() {
            using namespace Details::Enum;


            auto&& reflector = EnumReflector::Create<SomeEnum>();

            if (reflector.GetName() != "SomeEnum")
                return false;

            if (reflector.GetByKey("THREE" ).GetValue() != thirdFieldValue)
                return false;

            if (reflector.Size() != 4)
                return false;

            auto&& it = reflector.begin();
            for (i32 i = 0; it != reflector.end(); i++, it++)
                if (*it != reflector.At(i))
                    return false;

            return true;
        }
    };
}