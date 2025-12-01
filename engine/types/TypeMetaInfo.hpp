#pragma once

#include <types/hash/Hash.hpp>


#define KIWI_CREATE_TYPEINFO_FUNC(ClassName)     Kiwi::TypeMetaInfo(StringView{ KIWI_MAKE_STRING(ClassName) })


namespace Kiwi {
    using TypeHash = Hash64;

    class TypeMetaInfo {
    private:
        TypeHash m_typeHash;
        String m_typeName;

    public:
        TypeMetaInfo() = default;
        explicit TypeMetaInfo(StringView typeName);

        KIWI_NODISCARD const String& GetTypeName() const;
        KIWI_NODISCARD TypeHash GetType() const;

        KIWI_NODISCARD bool operator==(const TypeMetaInfo& other) const noexcept;
        KIWI_NODISCARD bool operator!=(const TypeMetaInfo& other) const noexcept;
    };
}
