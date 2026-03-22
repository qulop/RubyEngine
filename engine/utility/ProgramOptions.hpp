#pragma once

#include <common/StdInc.hpp>

#include <common/cast/Cast.hpp>
#include <utility/Definitions.hpp>


namespace Kiwi {
    enum class EOptionArgType {
        NONE,
        INT, BOOL,
        STRING,
        PATH
    };

    template<>
    struct CastTraits<EOptionArgType> {
        KIWI_NODISCARD KIWI_FORCEINLINE static Opt<String> ToString(EOptionArgType t) {
            switch (t) {
                case EOptionArgType::INT:
                    return "int";
                case EOptionArgType::BOOL:
                    return "bool";
                case EOptionArgType::STRING:
                    return "string";
                case EOptionArgType::PATH:
                    return "path";
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
        KIWI_NODISCARD static EOptionArgType DeduceArgumentType(StringView arg) noexcept;
        KIWI_NODISCARD static bool CheckArgumentType(StringView arg, EOptionArgType expected) noexcept;
    };


    class KIWI_API ProgramOptions {
        using ArgumentType = std::variant<std::monostate, i32, bool, String, Path>;
        using ArgumentsMapType = HashMap<String, ArgumentType>;

    public:
        KIWI_NODISCARD static Opt<ProgramOptions> Parse(const Vector<String>& args);

    public:
        ProgramOptions() = default;

        ProgramOptions(const ProgramOptions& other);
        ProgramOptions(ProgramOptions&& other) noexcept;

        KIWI_NODISCARD bool IsEmpty() const;
        KIWI_NODISCARD bool HasOption(const String& opt) const;

        template<typename T>
        KIWI_NODISCARD Opt<T> Get(const String& opt) const {
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
        KIWI_NODISCARD static Opt<String> GetOptionName(StringView opt);
        KIWI_NODISCARD static Opt<ArgumentType> ParseArgument(StringView arg, const CmdLineOption& opt);

    private:
        ArgumentsMapType m_options;
    };
}