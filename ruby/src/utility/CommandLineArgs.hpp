#pragma once

#include "StdInc.hpp"
#include "Definitions.hpp"


namespace Ruby {
    struct RUBY_API CommandLineArgs {
        int argc = 0;
        char** argv = nullptr;
        RubyString app_path;


        CommandLineArgs() = default;
        CommandLineArgs(int argc, char** argv);
        CommandLineArgs(const CommandLineArgs& other);
        CommandLineArgs(CommandLineArgs&& other) noexcept;

        cstr operator[](size_t i) const;

        CommandLineArgs& operator=(const CommandLineArgs& other);
        CommandLineArgs& operator=(CommandLineArgs&& other) noexcept;

        ~CommandLineArgs();

    private:
        void CopyArgv(char** argv);
    };
}