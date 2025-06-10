#pragma once

#include <utility/Assert.hpp>
#include <framework/RubyTestsFramework.hpp>
#include <utility/Definitions.hpp>


RUBY_TESTS_SUITE {
    RUBY_DEFINE_TEST("AssertTest", Assert) {
        RUBY_TESTS_ASSERT_MUST_ABORT(RUBY_ASSERT_BASIC(false));

        RUBY_TESTS_ASSERT_FALSE(RUBY_ASSERT(false, "1 == 2"));

        RUBY_TESTS_ASSERT_TRUE(RUBY_ASSERT(true, "2 == 2"));
        
        RUBY_TESTS_ASSERT_TRUE(RUBY_ASSERT_BASIC("AlwaysTrue"));
    }
}

