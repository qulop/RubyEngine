#include <platform/Platform.hpp>    // Logger doesn't initialize at this moment, so we need to use Console::Write() or Platform::writeInConsole()

#include <types/CString.hpp>
#include <types/String.hpp>
#include <types/cast/Cast.hpp>
#include <types/cast/StringCasts.hpp>

#include <utility/ProgramOptions.hpp>
#include <utility/Assert.hpp>
#include <utility/Panic.hpp>

#include <core/EngineConfig.hpp>


namespace Ruby {
    EOptionArgType CmdLineOption::DeduceArgumentType(StringView arg) noexcept {
        RUBY_ASSERT_BASIC(!arg.empty() && !arg.starts_with('-'));

        if (arg == "true" || arg == "false") {
            return EOptionArgType::BOOL;
        }
        if (Cast<String>::ToIntI64(arg).has_value()) {
            return EOptionArgType::INT;
        }
        return EOptionArgType::STRING;
    }

    bool CmdLineOption::CheckArgumentType(StringView arg, EOptionArgType expected) noexcept {
        if (arg.empty() || arg.starts_with('-')) {
            return false;
        }

        return DeduceArgumentType(arg) == expected;
    }


    ProgramOptions::ProgramOptions(const ProgramOptions& other) {
        *this = other;
    }

    ProgramOptions::ProgramOptions(ProgramOptions&& other) noexcept {
        *this = std::move(other);
    }

    Opt<ProgramOptions> ProgramOptions::Parse(const Vector<String>& args) {
        ProgramOptions result;
        auto existingOptions = EngineConfig::GetCommandLineOptions();

        for (size_t tokenIndex = 0; tokenIndex < args.size(); tokenIndex++) {
            const String& token = args.at(tokenIndex);

            // Stars with '-' sign and contains the letter in the second cell
            if ((token.size() > 1 && token.starts_with('-')) && std::isalpha(token.at(1))) {
                Console::WriteLine("An argument doesn't apply to any flag: \"{}\"", token);
                continue;
            }

            Opt<String> optionName = GetOptionName(token);
            if (!optionName) {
                Console::WriteLine("Token \"{}\" not recognized as an option", token);
                return nullopt;
            }

            auto foundOption = std::ranges::find(existingOptions, optionName.value(), &CmdLineOption::name);
            if (foundOption == existingOptions.end()) {
                Console::WriteLine("Unknown option \"{}\"", optionName.value());
                return nullopt;
            }

            // Just a flag case - just adding the std::monostate{}(i.e. "nothing")
            if (foundOption->type == EOptionArgType::NONE) {
                result.m_options[foundOption->name] = std::monostate{};
                continue;
            }

            tokenIndex += 1;
            const String& argToken = (tokenIndex < args.size()) ? args.at(tokenIndex) : StringUtils::EmptyString();

            Opt<ArgumentType> argument = ParseArgument(argToken, *foundOption);
            if (!argument) {
                Console::WriteLine("Failed to parse an argument for option \"-{}\". Invalid token: \"{}\". <{}> type expected instead",
                    optionName.value(), argToken, Cast<EOptionArgType>::ToString(foundOption->type).value()
                );

                return nullopt;
            }


            result.m_options[optionName.value()] = *argument;
        }

        return result;
    }

    bool ProgramOptions::IsEmpty() const {
        return m_options.empty();
    }

    bool ProgramOptions::HasOption(const String& opt) const {
        return m_options.contains(opt);
    }

    ProgramOptions& ProgramOptions::operator=(const ProgramOptions& other) {
        if (this == &other) {
            return *this;
        }

        m_options = other.m_options;

        return *this;
    }

    ProgramOptions& ProgramOptions::operator=(ProgramOptions&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        m_options = std::move(other.m_options);

        return *this;
    }

    Opt<String> ProgramOptions::GetOptionName(StringView opt) {
        size_t beginOfFlagName = opt.find_first_not_of('-');
        if (beginOfFlagName == StringView::npos) {
            return nullopt;
        }

        return String{ opt.substr(beginOfFlagName) };
    }

    Opt<ProgramOptions::ArgumentType> ProgramOptions::ParseArgument(StringView arg, const CmdLineOption& opt) {
        RUBY_ASSERT(opt.type != EOptionArgType::NONE, "Hmm... Looks like someone pass a wrong option here (๏ᆺ๏υ)");

        if (!CmdLineOption::CheckArgumentType(arg, opt.type)) {
            return nullopt;
        }

        if (opt.type == EOptionArgType::INT) {
            return Cast<String>::ToIntI32(arg).value();
        }
        if (opt.type == EOptionArgType::BOOL) {
            return Cast<String>::ToBool(arg).value();
        }

        return String{ arg };
    }
}