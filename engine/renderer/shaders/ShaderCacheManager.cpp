#include "ShaderCacheManager.hpp"

#include <types/cast/Cast.hpp>
#include <types/Logger.hpp>

#include <ranges>


namespace {
    Ruby::Hash64 hash64FromNameString(Ruby::StringView name) {
        return Ruby::Hash64::ParseString(name).value_or(Ruby::Hash64{});
    }
}


namespace Ruby {
    ShaderCacheEntry ShaderCacheEntry::FromFileContent(const FileContent& fc) {
        return ShaderCacheEntry{ fc.GetAsBytesStream<u32>()};
    }


    bool ShaderCacheManager::Init() {
        return ShaderCacheManager::GetInstance().CreateGlobalCacheDirectoryOnInit();
    }

    RUBY_NODISCARD bool ShaderCacheManager::AddToCache(Hash64 key, const ShaderCacheEntry& data) {
        // TODO: Potential race condition in this function
        FileContent byteCode{ EFileContentDataFormat::BINARY, data.spriVByteCode };

        return AddToLocalCache(key, data) && AddToGlobalCache(key.ToString(), byteCode, /*isBinaryFormat=*/ true);
    }

    RUBY_NODISCARD Opt<ShaderCacheEntry> ShaderCacheManager::GetFromLocalCache(Hash64 key) const {
        u64 h = key.GetHashValue();

        RUBY_SCOPED_LOCK(m_localCacheGuard);

        auto it = m_localCache.find(h);
        if (it == m_localCache.end()) {
            return nullopt;
        }

        return it->second;
    }

    RUBY_NODISCARD Opt<ShaderCacheEntry> ShaderCacheManager::GetOrAddToLocalCache(Hash64 key, const ShaderCacheEntry& data) {
        RUBY_SCOPED_LOCK(m_localCacheGuard);

        u64 h = key.GetHashValue();
        if (m_localCache.contains(h)) {
            return m_localCache.at(h);
        }
        else {
            m_localCache[h] = data;
            return data;
        }
    }

    RUBY_NODISCARD bool ShaderCacheManager::IsInLocalCache(Hash64 key) const {
        return GetFromLocalCache(key).has_value();
    }

    RUBY_NODISCARD bool ShaderCacheManager::AddToLocalCache(Hash64 key, const ShaderCacheEntry& data) {
        RUBY_SCOPED_LOCK(m_localCacheGuard);

        m_localCache[key.GetHashValue()] = data;
        return true;
    }

    void ShaderCacheManager::RemoveFromLocalCache(Hash64 key) {
        RUBY_SCOPED_LOCK(m_localCacheGuard);

        m_localCache.erase(key.GetHashValue());
    }

    void ShaderCacheManager::ClearLocalCache() {
        RUBY_SCOPED_LOCK(m_localCacheGuard);

        m_localCache.clear();
    }
    
    Opt<ShaderCacheEntry> ShaderCacheManager::TryToFindCachedShader(Hash64 hashedShaderSource) {
        if (hashedShaderSource.IsEmpty()) {
            RUBY_ERROR("ShaderCacheManager::TryToFindCachedShader() : Failed to convert hashedShaderSource into the string");
            return nullopt;
        }

        Opt<ShaderCacheEntry> optCacheEntry = GetFromLocalCache(hashedShaderSource)
            .or_else([&]() {
                return GetFromGlobalCache(hashedShaderSource.ToString())
                    .transform(&ShaderCacheEntry::FromFileContent);
            }
        );

        if (!optCacheEntry) {
            return nullopt;
        }
         
        RUBY_DEBUG("ShaderCacheManager::TryToFindCachedShader() : The shader \"{}\" successfully loaded from the cache",
                   hashedShaderSource
        );

        return optCacheEntry.value();
    }
}