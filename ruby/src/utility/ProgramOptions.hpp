#pragma once

#include <types/StdInc.hpp>
#include "Definitions.hpp"


namespace Ruby {
    RUBY_ENUM(OptionArgumentsTypes,
        CLI_ARG_NONE,
        CLI_ARG_INT, CLI_ARG_BOOL,
        CLI_ARG_STRING
    );

    struct CmdLineOption {
        using ArgumentType = std::variant<std::monostate, int, bool, RubyString>;

        RubyString longName;
        OptionArgumentsTypes type = CLI_ARG_STRING;
        ArgumentType defaultValue;

        CmdLineOption() = default;
        CmdLineOption(RubyString longName, OptionArgumentsTypes type, ArgumentType defaultValue) :
            longName(std::move(longName)),
            type(type),
            defaultValue(std::move(defaultValue)
        {}
    };


    class RUBY_API ProgramOptions {
        using OptionsMapType = std::unordered_map<RubyString, CmdLineOption>;
    public:
        ProgramOptions(int argc, char** argv, std::initializer_list<CmdLineOption> opts);
        ProgramOptions(const ProgramOptions& other);
        ProgramOptions(ProgramOptions&& other) noexcept;

        static bool IsFlag(const char* arg);

        char* At(size_t i);
        char* operator[](size_t i);

        RUBY_NODISCARD bool IsOptionPresent(const RubyString& opt) const;
        RUBY_NODISCARD auto GetArgumentOfOption(const RubyString& opt) const;


        RUBY_NODISCARD int GetCount() const;
        char** GetRawArguments();
        RUBY_NODISCARD RubyString GetAppPath() const;

        ProgramOptions& operator=(const ProgramOptions& other);
        ProgramOptions& operator=(ProgramOptions&& other) noexcept;

        ~ProgramOptions();
        
    private:
        RUBY_NODISCARD bool ExtractOptionName(RubyString& arg) const;
        RUBY_NODISCARD bool IsOptionExistsInMap(const OptionsMapType& map, const RubyString& flag) const;

        OptionsMapType CreateMapOfOptions(const CmdLineOption* begin, const CmdLineOption* end) const;
        bool ParseArgumentForOption(const CmdLineOption& opt, const char* arg);
        void CopyOptions(char** argv);
        
    private:
        int m_argc = 0;
        char** m_argv = nullptr;
        RubyString m_appPath;

        RubyHashMap<RubyString, typename CmdLineOption::ArgumentType> m_options;
    };
}