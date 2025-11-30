#pragma once

#include <types/hash/Hash.hpp>


#define RUBY_CREATE_TYPEINFO_FUNC(ClassName)     Ruby::TypeMetaInfo(StringView{ RUBY_MAKE_STRING(ClassName) })


namespace Ruby {
    using TypeHash = Hash64;

    class TypeMetaInfo {
    private:
        TypeHash m_typeHash;
        String m_typeName;

    public:
        TypeMetaInfo() = default;
        explicit TypeMetaInfo(StringView typeName);

        RUBY_NODISCARD const String& GetTypeName() const;
        RUBY_NODISCARD TypeHash GetType() const;

        RUBY_NODISCARD bool operator==(const TypeMetaInfo& other) const noexcept;
        RUBY_NODISCARD bool operator!=(const TypeMetaInfo& other) const noexcept;
    };
}
