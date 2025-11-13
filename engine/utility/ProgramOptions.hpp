#pragma once

#include <types/StdInc.hpp>

#include <types/cast/Cast.hpp>
#include <utility/Definitions.hpp>


namespace Ruby {
    enum class EOptionArgType {
        NONE,
        INT, BOOL,
        STRING
    };

    template<>
    struct CastTraits<EOptionArgType> {
        RUBY_NODISCARD RUBY_FORCEINLINE static Opt<String> ToString(EOptionArgType t) {
            switch (t) {
                case EOptionArgType::INT:
                    return "int";
                case EOptionArgType::BOOL:
                    return "bool";
                case EOptionArgType::STRING:
                    return "string";
                default:
                    return "none";
            }
        }
    };


    struct CmdLineOption {
    public:
        String name;
        EOptionArgType type = EOptionArgType::STRING;

    public:
        CmdLineOption() = default;
        CmdLineOption(String name, EOptionArgType type) :
            name(std::move(name)),
            type(type)
        {}

    public:
        RUBY_NODISCARD static EOptionArgType DeduceArgumentType(StringView arg) noexcept;
        RUBY_NODISCARD static bool CheckArgumentType(StringView arg, EOptionArgType expected) noexcept;
    };


    class RUBY_API ProgramOptions {
        using ArgumentType = std::variant<std::monostate, i32, bool, String>;
        using ArgumentsMapType = HashMap<String, ArgumentType>;

    public:
        RUBY_NODISCARD static Opt<ProgramOptions> Parse(const Vector<String>& args);

    public:
        ProgramOptions() = default;

        ProgramOptions(const ProgramOptions& other);
        ProgramOptions(ProgramOptions&& other) noexcept;

        RUBY_NODISCARD bool IsEmpty() const;
        RUBY_NODISCARD bool HasOption(const String& opt) const;

        template<typename T>
        RUBY_NODISCARD Opt<T> GetOptionArgument(const String& opt) const {
            if (!HasOption(opt) || std::holds_alternative<std::monostate>(m_options.at(opt))) {
                return nullopt;
            }

            if (const T* res = std::get_if<T>(&m_options.at(opt))) {
                return *res;
            }

            return nullopt;
        }

        ProgramOptions& operator=(const ProgramOptions& other);
        ProgramOptions& operator=(ProgramOptions&& other) noexcept;


        ~ProgramOptions() = default;
        
    private:
        RUBY_NODISCARD static Opt<String> GetOptionName(StringView opt);
        RUBY_NODISCARD static Opt<ArgumentType> ParseArgument(StringView arg, const CmdLineOption& opt);

    private:
        ArgumentsMapType m_options;
    };
}