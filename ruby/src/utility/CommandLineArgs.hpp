#pragma once

#include <types/StdInc.hpp>
#include "Definitions.hpp"


namespace Ruby {
    struct RUBY_API CommandLineArgs {
        int argc = 0;
        char** argv = nullptr;
        RubyString appPath;


        CommandLineArgs() = default;
        CommandLineArgs(int argc, char** argv);
        CommandLineArgs(const CommandLineArgs& other);
        CommandLineArgs(CommandLineArgs&& other) noexcept;

        char* At(size_t i) const;

        char* operator[](size_t i) const;

        CommandLineArgs& operator=(const CommandLineArgs& other);
        CommandLineArgs& operator=(CommandLineArgs&& other) noexcept;

        ~CommandLineArgs();

    private:
        void CopyArgv(char** argv);
    };
}