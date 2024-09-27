#include "ProgramOptions.hpp"

#include <utility/Assert.hpp>
#include <types/Logger.hpp>


namespace Ruby {
    OptionArgumentsTypes deduceTypeOfArgument(const char* arg) {
        if (std::strcmp(arg, "true") == 0 || std::strcmp(arg, "false") == 0)
            return CLI_ARG_BOOL;
        else if (strToInt<i32>(arg).has_value())
            return CLI_ARG_INT;
        return CLI_ARG_STRING;
    }




    ProgramOptions::ProgramOptions(int argc, char** argv, std::initializer_list<CmdLineOption> opts) :
            m_argc(argc),
            m_appPath(argv[0])
    {
        CopyOptions(argv);
        RUBY_ASSERT_BASIC(m_argv != nullptr);

        bool hasError = false;
        OptionsMapType optionsMap = std::move(CreateMapOfOptions(opts.begin(), opts.end())); 
        
        for (auto i = 0; i < m_argc; i++) {
            RubyString token = At(i);

            if (!IsFlag(token.c_str())) {
                RUBY_WARNING("ProgramOptions::ProgramOptions() : Argument doesn't apply to any flag: {}", token);
                continue;
            }

            bool hasErrorOnIteration = (!ExtractOptionName(token)
                    || !IsOptionExistsInMap(optionsMap, token)
                    || !ParseArgumentForOption(optionsMap.at(token), At(i + 1)));

            if (hasErrorOnIteration)
                hasError = true;
            i += (optionsMap.at(token).type == CLI_ARG_NONE) ? 0 : 1;
        }

        if (hasError)
            RUBY_CRITICAL("ProgramOptions::ProgramOptions() : Failed to parse passed options");
    }

    ProgramOptions::ProgramOptions(const ProgramOptions& other) {
        *this = other;
    }

    ProgramOptions::ProgramOptions(ProgramOptions&& other) noexcept {
        *this = std::move(other);
    }


    bool ProgramOptions::IsFlag(const char* arg) {
        return (arg != nullptr && arg[0] == '-');
    }

    char* ProgramOptions::At(size_t i) {
        return operator[](i);
    }

    char* ProgramOptions::operator[](size_t i) {
        RUBY_ASSERT(i < m_argc, "Index out of borders");

        return m_argv[i];
    }

    bool ProgramOptions::IsOptionPresent(const RubyString& opt) const {
        return m_options.contains(opt);
    }

    auto ProgramOptions::GetArgumentOfOption(const RubyString& opt) const {
        if (!IsOptionPresent(opt) || std::holds_alternative<std::monostate>(m_options.at(opt)))
            return std::any{};

        auto variantGetter = [](const auto& val) -> std::any {
            return std::make_any<std::decay_t<decltype(val)>>(val);
        };

        return std::visit(variantGetter, m_options.at(opt));
    }

    int ProgramOptions::GetCount() const {
        return m_argc;
    }

    char** ProgramOptions::GetRawArguments() {
        return m_argv;
    }

    RubyString ProgramOptions::GetAppPath() const {
        return m_appPath;
    }


    ProgramOptions& ProgramOptions::operator=(const ProgramOptions& other) {
        if (this == &other)
            return *this;

        m_argc = other.m_argc;
        m_appPath = other.m_appPath;
        CopyOptions(other.m_argv);

        return *this;
    }

    ProgramOptions& ProgramOptions::operator=(ProgramOptions&& other) noexcept {
        if (this == &other)
            return *this;

        m_argc = other.m_argc;
        m_argv = other.m_argv;
        m_appPath = std::move(other.m_appPath);

        other.m_argc = 0;
        other.m_argv = nullptr;

        return *this;
    }

    ProgramOptions::~ProgramOptions() {
        delete[] m_argv;
    }



    bool ProgramOptions::ExtractOptionName(RubyString& arg) const {
        size_t beginOfFlagName = arg.find_first_not_of('-');
        if (beginOfFlagName == std::string::npos) {
            RUBY_ERROR("ProgramOptions::ExtractFlagName() : Failed to find name of flag");
            return false;
        }

        arg.erase(0, beginOfFlagName);
        return true;
    }

    bool ProgramOptions::IsOptionExistsInMap(const ProgramOptions::OptionsMapType& map, const RubyString& flag) const {
        if (map.contains(flag))
            return true;

        RUBY_ERROR("ProgramOptions::IsFlagExistsInMap() : Unknown flag is found - {}", flag);
        return false;
    }


    ProgramOptions::OptionsMapType ProgramOptions::CreateMapOfOptions(const CmdLineOption* begin, const CmdLineOption* end) const {
        OptionsMapType ret;
        for (auto opt = begin; opt != end; opt++)
            ret[opt->longName] = *opt;

        return ret;
    }

    bool ProgramOptions::ParseArgumentForOption(const CmdLineOption& opt, const char* arg) {
        if (opt.type == CLI_ARG_NONE) {
            m_options[opt.longName] = std::monostate{};
            return true;
        }

        if (!arg) {
            RUBY_ERROR("ProgramOptions::ParseArgumentForOption() : Missing argument for option \"--{}\"",
               opt.longName);
            return false;
        }

        auto& reflector = EnumReflector::Create<OptionArgumentsTypes>();
        if (auto argType = deduceTypeOfArgument(arg); argType != opt.type) {
                RUBY_ERROR("ProgramOptions::ParseArgumentForOption() : Option \"--{}\" expects argument of type {}, but gets {}",
                   opt.longName, reflector.GetByValue(opt.type), reflector.GetByValue(argType));
            return false;
        }

        switch (opt.type) {
            case CLI_ARG_INT:
                m_options[opt.longName] = strToInt<i32>(arg).value();
            case CLI_ARG_BOOL:
                m_options[opt.longName] = strToBool(arg).value();
            default:
                m_options[opt.longName] = RubyString{ arg };
        }
        return true;
    }

    void ProgramOptions::CopyOptions(char** args) {
        m_argv = new char*[m_argc];  // content of m_argv(without path) + nullptr limiter

        for (auto i = 1; i < m_argc; i++) {
            size_t len = std::strlen(args[i]) + 1;
            m_argv[i-1] = new char[len];
            strcpy_s(m_argv[i-1], len, args[i]);
        }

        m_argv[m_argc - 1] = nullptr;
    }
}