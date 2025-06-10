#pragma once

#include <utility/ProgramOptions.hpp>
#include <framework/RubyTestsFramework.hpp>


RUBY_TESTS_SUITE {
    RUBY_DEFINE_TEST("ProgramOptionsTest", ProgramOptions) {
        std::array<const char*, 4> cmdLineTokens = { "/path/to/executable", "--width", "100", "--" }; 
        i32 argc = static_cast<i32>(cmdLineTokens.size());
        char** argv = &cmdLineTokens.front();

        ProgramOptions options{ argc, argv, {
                { "width", CLI_ARG_INT, 200 },
                { "help", CLI_ARG_NONE },
                { "resizable", CLI_ARG_BOOL, true },
                { "log-directory", CLI_ARG_STRING, "." }
        }};


        RUBY_TESTS_ASSERT_EQ(argc, options.GetCount());
        RUBY_TESTS_ASSERT_TRUE(options.IsOptionPresent("width"));

        auto argumentOfOption = options.GetArgumentOfOption("width");
        RUBY_TESTS_ASSERT_EQ(true, argumentOfOption.has_value());
        RUBY_TESTS_ASSERT_EQ(100, std::any_cast<i32>(argumentOfOption));


    }
}
