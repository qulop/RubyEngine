#pragma once

#include <types/TypeTraits.hpp>
#include <types/FileContent.hpp>
#include <types/Logger.hpp>
#include <types/File.hpp>

#include <sync/Mutex.hpp>

#include <utility/Definitions.hpp>


namespace Ruby::Globals {
    constexpr StringView ROOT_CACHE_DIR = "cache";
}

namespace Ruby::Traits {
    template<typename TCachedObject>
    struct CacheManagerTraits;
}

namespace Ruby {
    template<std::copyable TCachedObject>
    RUBY_ABSTRACT class LayeredCacheManagerBase {
    protected:
        LayeredCacheManagerBase() :
            m_cacheDirectoryName(Traits::CacheManagerTraits<TCachedObject>::defaultCacheDirName)
        {}

    public:
#pragma region Virtual function to implement in successor: local cache and adding to both caches
        virtual RUBY_NODISCARD bool AddToCache(StringView name, const TCachedObject& data) = 0;


        virtual RUBY_NODISCARD Opt<TCachedObject> GetFromLocalCache(StringView name) const = 0;

        virtual RUBY_NODISCARD Opt<TCachedObject> GetOrAddToLocalCache(StringView name, const TCachedObject& data) = 0;

        virtual RUBY_NODISCARD bool IsInLocalCache(StringView name) const = 0;

        virtual RUBY_NODISCARD bool AddToLocalCache(StringView name, const TCachedObject& data) = 0;

        virtual void RemoveFromLocalCache(StringView name) = 0;

        virtual void ClearLocalCache() = 0;
#pragma endregion

#pragma region Default implementation of global cache/L2 cache
        RUBY_NODISCARD Opt<FileContent> GetFromGlobalCache(StringView name, bool isBinaryFormat = true) const {
            RUBY_SCOPED_LOCK(m_globalCacheGuard);

            auto targetFilePath = GetPathToCachedFile_NoLock(name);
            if (!std::filesystem::exists(targetFilePath)) {
                return nullopt;
            }

            return File::LoadFromFile(
                std::move(targetFilePath),
                (isBinaryFormat) ?
                    EFileOpenMode::READ | EFileOpenMode::BINARY :
                    EFileOpenMode::READ
            );
        }

        RUBY_NODISCARD Opt<FileContent> GetOrAddToGlobalCache(StringView name, const FileContent& data, bool isBinaryFormat) const {
            if (auto optRes = GetFromGlobalCache(name); optRes.has_value()) {
                return *optRes;
            }

            if (!AddToGlobalCache(name, data, isBinaryFormat)) {
                return nullopt;
            }
            return data;
        }

        RUBY_FORCEINLINE RUBY_NODISCARD bool IsInCache(StringView name) const {
            return IsInLocalCache(name) || IsInGlobalCache(name);
        }

        RUBY_FORCEINLINE RUBY_NODISCARD bool IsInGlobalCache(StringView name) const {
            RUBY_SCOPED_LOCK(m_globalCacheGuard);

            return std::filesystem::exists(GetPathToCachedFile_NoLock(name));
        }

        RUBY_NODISCARD bool AddToGlobalCache(StringView name, const FileContent& data, bool isBinaryFormat, bool overwrite = true) const {
            RUBY_SCOPED_LOCK(m_globalCacheGuard);

            auto targetPath = GetPathToCachedFile_NoLock(name);
            if (std::filesystem::exists(targetPath) && !overwrite) {
                return false;
            }

            return File::SaveInFile(std::move(targetPath), data, isBinaryFormat, overwrite);
        }

        void RemoveFromCache(StringView name) {
            RemoveFromLocalCache(name);

            RUBY_SCOPED_LOCK(m_globalCacheGuard);

            std::error_code ec;
            if (!std::filesystem::remove(std::move(GetPathToCachedFile(name)), ec)) {
                RUBY_ERROR("ShaderManager::RemoveFromCache() : Failed to remove a file {} - {}", name, ec.message());
            }
        }

        void ClearAllCache() {
            ClearLocalCache();

            RUBY_SCOPED_LOCK(m_globalCacheGuard);
            std::filesystem::remove_all(std::move(GetCacheDirAbsolutePath_NoLock()));
        }

        RUBY_NODISCARD Path GetCacheDirAbsolutePath() const {
            RUBY_SCOPED_LOCK(m_globalCacheGuard);

            return GetCacheDirAbsolutePath_NoLock();
        }

        RUBY_FORCEINLINE RUBY_NODISCARD Path GetPathToCachedFile(StringView fileName) const {
            RUBY_SCOPED_LOCK(m_globalCacheGuard);

            return GetPathToCachedFile_NoLock(fileName);
        }

        RUBY_FORCEINLINE RUBY_NODISCARD String GetCacheDirName() const {
            RUBY_SCOPED_LOCK(m_globalCacheGuard);

            return m_cacheDirectoryName;
        }

        RUBY_FORCEINLINE void ChangeCacheDirectoryName(StringView newName) {
            RUBY_SCOPED_LOCK(m_globalCacheGuard);

            m_cacheDirectoryName = newName;
        }


        virtual ~LayeredCacheManagerBase() = default;

    protected:
        RUBY_NODISCARD bool CreateGlobalCacheDirectoryOnInit() {
            RUBY_ASSERT_BASIC(!m_cacheDirectoryName.empty());

            if (!std::filesystem::create_directory(GetCacheDirAbsolutePath_NoLock())) {
                RUBY_ERROR("LayeredCacheManagerBase::CreateGlobalCacheDirectoryOnInit() : Failed to create cache directory: {}",
                    m_cacheDirectoryName
                );
                return false;
            }

            return true;
        }

    private:
        RUBY_NODISCARD Path GetCacheDirAbsolutePath_NoLock() const {
            return std::filesystem::absolute(Path{ Globals::ROOT_CACHE_DIR }) / m_cacheDirectoryName;
        }

        RUBY_NODISCARD Path GetPathToCachedFile_NoLock(StringView fileName) const {
            return GetCacheDirAbsolutePath_NoLock() / fileName;
        }

    private:
        mutable Sync::Mutex m_globalCacheGuard;

        String m_cacheDirectoryName;
    };
#pragma endregion
}