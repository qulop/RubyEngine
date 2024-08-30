#pragma once

#include <tests/framework/RubyTestsFramework.hpp>
#include <utility/Definitions.hpp>

#define _RUBY_CONFIG_ASSERT_IGNORE_OUTPUT
#define _RUBY_CONFIG_ASSERT_IGNORE_ABORT

RUBY_TESTS_SUITE {
    namespace MyAssert = Ruby::Details::Assert;

    RUBY_DEFINE_TEST("AssertTest", Assert) {
        RUBY_TESTS_ASSERT_FALSE(RUBY_ASSERT(false, "1 == 2"));

        RUBY_TESTS_ASSERT_TRUE(RUBY_ASSERT(true, "2 == 2"));
        
        RUBY_TESTS_ASSERT_TRUE(RUBY_ASSERT_BASIC("AlwaysTrue"));
    }
}

#undef _RUBY_CONFIG_ASSERT_IGNORE_OUTPUT
#undef _RUBY_CONFIG_ASSERT_IGNORE_ABORT