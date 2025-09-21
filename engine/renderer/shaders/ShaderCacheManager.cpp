#include "ShaderCacheManager.hpp"

#include <types/Cast.hpp>
#include <types/Logger.hpp>

#include <ranges>


namespace {
    Ruby::hash_t getHashFromNameString(Ruby::StringView name) {
        return Ruby::Cast<Ruby::String>::ToHash(name, /*base=*/ 10).value_or(0);
    }
}

namespace Ruby {
    ShaderCacheEntry ShaderCacheEntry::FromFileContent(const FileContent& fc) {
        return ShaderCacheEntry{ fc.GetAsBytesStream<u32>()};
    }


    bool ShaderCacheManager::Init() {
        return ShaderCacheManager::GetInstance().CreateGlobalCacheDirectoryOnInit();
    }


#pragma region LayeredCacheManagerBase Abstract Class Implementation
    bool ShaderCacheManager::AddToCache(StringView name, const ShaderCacheEntry& data) {
        // TODO: Potential race condition in this function
        FileContent byteCode{ EFileContentDataFormat::BINARY, data.spriVByteCode };

        return AddToLocalCache(name, data) && AddToGlobalCache(name, byteCode, /*isBinaryFormat=*/ true);
    }

    Opt<ShaderCacheEntry> ShaderCacheManager::GetFromLocalCache(StringView name) const {
        hash_t hashToFind = getHashFromNameString(name);

        RUBY_SCOPED_LOCK(m_localCacheGuard);
        if (!m_localCache.contains(hashToFind)) {
            return nullopt;
        }

        return m_localCache.at(hashToFind);
    }

    RUBY_NODISCARD Opt<ShaderCacheEntry> ShaderCacheManager::GetOrAddToLocalCache(StringView name, const ShaderCacheEntry& data) {
        RUBY_SCOPED_LOCK(m_localCacheGuard);

        if (auto h = getHashFromNameString(name); m_localCache.contains(h)) {
            return m_localCache.at(h);
        }
        else {
            m_localCache[h] = data;
            return data;
        }
    }

    bool ShaderCacheManager::IsInLocalCache(StringView name) const {
        return GetFromLocalCache(name).has_value();
    }

    bool ShaderCacheManager::AddToLocalCache(StringView name, const ShaderCacheEntry& data) {
        RUBY_SCOPED_LOCK(m_localCacheGuard);

        m_localCache[getHashFromNameString(name)] = data;
        return true;
    }

    void ShaderCacheManager::RemoveFromLocalCache(StringView name) {
        RUBY_SCOPED_LOCK(m_localCacheGuard);

        m_localCache.erase(getHashFromNameString(name));
    }

    void ShaderCacheManager::ClearLocalCache() {
        RUBY_SCOPED_LOCK(m_localCacheGuard);

        m_localCache.clear();
    }
#pragma endregion
}