#pragma once

#include <tests/framework/RubyTestsFramework.hpp>
#include <utility/Enum.hpp>


RUBY_TESTS_SUITE {
    namespace Details::Enum {
        RUBY_ENUM(TestedOuterEnum,
            ONE = 1 << 0,
            TWO = (1 << 1),
            THREE = (1 << 10),
            FOUR = ONE
        );
        constexpr i32 thirdFieldValue = THREE;

        struct Struct {
            RUBY_ENUM_INNER(TestedInnerEnum,
                        INNER_ONE,
                        INNER_TWO = 5000
                    )
        };
    }


    RUBY_DEFINE_TEST("OuterEnumTest", OuterEnum) {
        using namespace Details::Enum;
        auto&& reflector = EnumReflector::Create<TestedOuterEnum>();

        RUBY_TESTS_ASSERT_EQ("SomeEnum", reflector.GetName());

        RUBY_TESTS_ASSERT_EQ(thirdFieldValue, reflector.GetByKey("THREE").GetValue());
 
        RUBY_TESTS_ASSERT_EQ(4, reflector.Size());

        auto&& it = reflector.begin();
        for (i32 i = 0; it != reflector.end(); i++, it++)
            RUBY_TESTS_ASSERT_EQ(*it, reflector.At(i));
    }


    RUBY_DEFINE_TEST("InnerEnumTest", InnerEnum) {
        using namespace Details::Enum;
        auto&& reflector = EnumReflector::Create<Struct::TestedInnerEnum>();

        
    }
}