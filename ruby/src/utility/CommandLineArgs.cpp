#include "CommandLineArgs.hpp"


namespace Ruby {
    CommandLineArgs::CommandLineArgs(int argc, char** argv) :
            argc(argc),
            appPath(argv[0])
    {
        CopyArgv(argv);
    }

    CommandLineArgs::CommandLineArgs(const CommandLineArgs& other) {
        *this = other;
    }

    CommandLineArgs::CommandLineArgs(CommandLineArgs&& other) noexcept {
        *this = std::move(other);
    }

    char* CommandLineArgs::At(size_t i) const {
        return operator[](i);
    }

    char* CommandLineArgs::operator[](size_t i) const {
        RUBY_ASSERT(i < argc, "Index out of borders");

        return argv[i];
    }

    CommandLineArgs& CommandLineArgs::operator=(const CommandLineArgs& other) {
        if (this == &other)
            return *this;

        argc = other.argc;
        appPath = other.appPath;
        CopyArgv(other.argv);

        return *this;
    }

    CommandLineArgs& CommandLineArgs::operator=(CommandLineArgs&& other) noexcept {
        if (this == &other)
            return *this;

        argc = other.argc;
        argv = other.argv;
        appPath = std::move(other.appPath);

        other.argc = 0;
        other.argv = nullptr;

        return *this;
    }

    CommandLineArgs::~CommandLineArgs() {
        delete[] argv;
    }

    void CommandLineArgs::CopyArgv(char** args) {
        argv = new char*[argc];  // content of argv(without path) + nullptr limiter

        for (auto i = 1; i < argc; i++) {
            size_t len = std::strlen(args[i]) + 1;
            argv[i-1] = new char[len];
            strcpy_s(argv[i-1], len, args[i]);
        }

        argv[argc - 1] = nullptr;
    }
}