#include "CommandLineArgs.hpp"


namespace Ruby {
    CommandLineArgs::CommandLineArgs(int argc, char** argv) :
            argc(argc),
            app_path(argv[0])
    {
        CopyArgv(argv);
    }

    CommandLineArgs::CommandLineArgs(const CommandLineArgs& other) {
        *this = other;
    }

    CommandLineArgs::CommandLineArgs(CommandLineArgs&& other) noexcept {
        *this = std::move(other);
    }

    cstr CommandLineArgs::operator[](size_t i) const {
        RUBY_ASSERT(i < argc, "Index out of borders");

        return argv[i];
    }

    CommandLineArgs& CommandLineArgs::operator=(const CommandLineArgs& other) {
        if (this == &other)
            return *this;

        argc = other.argc;
        app_path = other.app_path;
        CopyArgv(other.argv);

        return *this;
    }

    CommandLineArgs& CommandLineArgs::operator=(CommandLineArgs&& other) noexcept {
        if (this == &other)
            return *this;

        argc = other.argc;
        argv = other.argv;
        app_path = std::move(other.app_path);

        other.argc = 0;
        other.argv = nullptr;

        return *this;
    }

    CommandLineArgs::~CommandLineArgs() {
        delete[] argv;
    }



    void CommandLineArgs::CopyArgv(char** argv) {
        if (argc == 1)
            return;

        this->argv = new char *[argc];

        for (auto i = 1; i < argc; i++) {
            size_t len = std::strlen(argv[i]);
            this->argv[i - 1] = new char[len];
            strcpy_s(this->argv[i - 1], len, argv[i]);
        }

        this->argv[argc - 1] = nullptr;
    }
}