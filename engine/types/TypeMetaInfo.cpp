#include "TypeMetaInfo.hpp"

#include <utility/Assert.hpp>


namespace Ruby {
    TypeMetaInfo::TypeMetaInfo(StringView typeName) :
      m_typeName(typeName)
    {
        auto hash = TypeHash::FromData(typeName.data(), typeName.size());
        RUBY_ASSERT(hash, "We should always have a hash from type name string!");

        m_typeHash = hash.value();
    }

    String TypeMetaInfo::GetTypeName() const {
        return m_typeName;
    }

    Hash64 TypeMetaInfo::GetTypeHash() const {
        return m_typeHash;
    }

    bool TypeMetaInfo::operator==(const TypeMetaInfo &other) const noexcept {
        return m_typeHash == other.m_typeHash;
    }

    bool TypeMetaInfo::operator!=(const TypeMetaInfo &other) const noexcept {
        return !(*this == other);
    }
}
