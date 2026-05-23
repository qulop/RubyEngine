#include "ShaderCacheManager.hpp"

#include <common/cast/Cast.hpp>

#include <ranges>


namespace Kiwi {
    ShaderCacheEntry ShaderCacheEntry::FromFileContent(const FileContent& fc) {
        return ShaderCacheEntry{ fc.GetAsBytesStream<u32>()};
    }


    StatusResult<EGeneralError> ShaderCacheManager::Init() {
        return ShaderCacheManager::GetInstance().CreateGlobalCacheDirectoryOnInit();
    }

    KIWI_NODISCARD bool ShaderCacheManager::AddToCache(Hash64 key, const ShaderCacheEntry& data) {
        // TODO: Potential race condition in this function
        FileContent byteCode{ EFileContentDataFormat::BINARY, data.spriVByteCode };

        return AddToLocalCache(key, data) && AddToGlobalCache(key.ToString().ToStringView(), byteCode, /*isBinaryFormat=*/ true);
    }

    KIWI_NODISCARD Opt<ShaderCacheEntry> ShaderCacheManager::GetFromLocalCache(Hash64 key) const {
        u64 h = key.GetHashValue();

        KIWI_SCOPED_LOCK(m_localCacheGuard);

        auto it = m_localCache.find(h);
        if (it == m_localCache.end()) {
            return nullopt;
        }

        return it->second;
    }

    KIWI_NODISCARD Opt<ShaderCacheEntry> ShaderCacheManager::GetOrAddToLocalCache(Hash64 key, const ShaderCacheEntry& data) {
        KIWI_SCOPED_LOCK(m_localCacheGuard);

        u64 h = key.GetHashValue();
        if (m_localCache.contains(h)) {
            return m_localCache.at(h);
        }
        else {
            m_localCache[h] = data;
            return data;
        }
    }

    KIWI_NODISCARD bool ShaderCacheManager::IsInLocalCache(Hash64 key) const {
        return GetFromLocalCache(key).has_value();
    }

    KIWI_NODISCARD bool ShaderCacheManager::AddToLocalCache(Hash64 key, const ShaderCacheEntry& data) {
        KIWI_SCOPED_LOCK(m_localCacheGuard);

        m_localCache[key.GetHashValue()] = data;
        return true;
    }

    void ShaderCacheManager::RemoveFromLocalCache(Hash64 key) {
        KIWI_SCOPED_LOCK(m_localCacheGuard);

        m_localCache.erase(key.GetHashValue());
    }

    void ShaderCacheManager::ClearLocalCache() {
        KIWI_SCOPED_LOCK(m_localCacheGuard);

        m_localCache.clear();
    }
    
    Opt<ShaderCacheEntry> ShaderCacheManager::TryToFindCachedShader(Hash64 hashedShaderSource) {
        if (hashedShaderSource.IsEmpty()) {
            return nullopt;
        }

        Opt<ShaderCacheEntry> optCacheEntry = GetFromLocalCache(hashedShaderSource)
            .or_else([&]() {
                return GetFromGlobalCache(hashedShaderSource.ToString().ToStringView())
                    .transform(&ShaderCacheEntry::FromFileContent);
            }
        );

        if (!optCacheEntry) {
            return nullopt;
        }


        return optCacheEntry.value();
    }
}