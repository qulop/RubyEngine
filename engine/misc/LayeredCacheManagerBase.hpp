#pragma once

#include <types/TypeTraits.hpp>
#include <types/FileContent.hpp>
#include <types/Logger.hpp>
#include <types/File.hpp>

#include <sync/Mutex.hpp>

#include <utility/Definitions.hpp>
#include <utility/Assert.hpp>


namespace Kiwi::Globals {
    constexpr StringView ROOT_CACHE_DIR = "cache";
}

namespace Kiwi::Traits {
    template<typename TCachedObject>
    struct CacheManagerTraits;
}

namespace Kiwi {
    template<typename TKey, std::copyable TCachedObject>
    KIWI_ABSTRACT class ALayeredCacheManagerBase {
    protected:
        ALayeredCacheManagerBase() :
            m_cacheDirectoryName(Traits::CacheManagerTraits<TCachedObject>::defaultCacheDirName)
        {}

    public:
        KIWI_NODISCARD virtual bool AddToCache(TKey key, const TCachedObject& data) = 0;

        KIWI_NODISCARD virtual Opt<TCachedObject> GetFromLocalCache(TKey key) const = 0;

        KIWI_NODISCARD virtual Opt<TCachedObject> GetOrAddToLocalCache(TKey key, const TCachedObject& data) = 0;

        KIWI_NODISCARD virtual bool IsInLocalCache(TKey key) const = 0;

        KIWI_NODISCARD virtual bool AddToLocalCache(TKey key, const TCachedObject& data) = 0;

        virtual void RemoveFromLocalCache(TKey key) = 0;

        virtual void ClearLocalCache() = 0;


        KIWI_NODISCARD Opt<FileContent> GetFromGlobalCache(StringView name, bool isBinaryFormat = true) const {
            KIWI_SCOPED_LOCK(m_globalCacheGuard);

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

        KIWI_NODISCARD Opt<FileContent> GetOrAddToGlobalCache(StringView name, const FileContent& data, bool isBinaryFormat) const {
            if (auto optRes = GetFromGlobalCache(name); optRes.has_value()) {
                return *optRes;
            }

            if (!AddToGlobalCache(name, data, isBinaryFormat)) {
                return nullopt;
            }
            return data;
        }

        KIWI_NODISCARD KIWI_FORCEINLINE bool IsInCache(StringView name) const {
            return IsInLocalCache(name) || IsInGlobalCache(name);
        }

        KIWI_NODISCARD KIWI_FORCEINLINE bool IsInGlobalCache(StringView name) const {
            KIWI_SCOPED_LOCK(m_globalCacheGuard);

            return std::filesystem::exists(GetPathToCachedFile_NoLock(name));
        }

        KIWI_NODISCARD bool AddToGlobalCache(StringView name, const FileContent& data, bool isBinaryFormat, bool overwrite = true) const {
            KIWI_SCOPED_LOCK(m_globalCacheGuard);

            auto targetPath = GetPathToCachedFile_NoLock(name);
            if (std::filesystem::exists(targetPath) && !overwrite) {
                return false;
            }

            return File::SaveInFile(std::move(targetPath), data, isBinaryFormat, overwrite);
        }

        void RemoveFromCache(StringView name) {
            RemoveFromLocalCache(name);

            KIWI_SCOPED_LOCK(m_globalCacheGuard);

            std::error_code ec;
            if (!std::filesystem::remove(std::move(GetPathToCachedFile(name)), ec)) {
                KIWI_ERROR("ShaderManager::RemoveFromCache() : Failed to remove a file {} - {}", name, ec.message());
            }
        }

        void ClearAllCache() {
            ClearLocalCache();

            KIWI_SCOPED_LOCK(m_globalCacheGuard);
            std::filesystem::remove_all(std::move(GetCacheDirAbsolutePath_NoLock()));
        }

        KIWI_NODISCARD Path GetCacheDirAbsolutePath() const {
            KIWI_SCOPED_LOCK(m_globalCacheGuard);

            return GetCacheDirAbsolutePath_NoLock();
        }

        KIWI_NODISCARD KIWI_FORCEINLINE Path GetPathToCachedFile(StringView fileName) const {
            KIWI_SCOPED_LOCK(m_globalCacheGuard);

            return GetPathToCachedFile_NoLock(fileName);
        }

        KIWI_NODISCARD KIWI_FORCEINLINE String GetCacheDirName() const {
            KIWI_SCOPED_LOCK(m_globalCacheGuard);

            return m_cacheDirectoryName;
        }

        KIWI_FORCEINLINE void ChangeCacheDirectoryName(StringView newName) {
            KIWI_SCOPED_LOCK(m_globalCacheGuard);

            m_cacheDirectoryName = newName;
        }


        virtual ~ALayeredCacheManagerBase() = default;

    protected:
        KIWI_NODISCARD bool CreateGlobalCacheDirectoryOnInit() {
            KIWI_ASSERT_BASIC(!m_cacheDirectoryName.empty());

            if (!std::filesystem::create_directory(GetCacheDirAbsolutePath_NoLock())) {
                KIWI_ERROR("ALayeredCacheManagerBase::CreateGlobalCacheDirectoryOnInit() : Failed to create cache directory: {}",
                    m_cacheDirectoryName
                );
                return false;
            }

            return true;
        }

    private:
        KIWI_NODISCARD Path GetCacheDirAbsolutePath_NoLock() const {
            return std::filesystem::absolute(Path{ Globals::ROOT_CACHE_DIR }) / m_cacheDirectoryName;
        }

        KIWI_NODISCARD Path GetPathToCachedFile_NoLock(StringView fileName) const {
            return GetCacheDirAbsolutePath_NoLock() / fileName;
        }

    private:
        mutable Sync::Mutex m_globalCacheGuard;

        String m_cacheDirectoryName;
    };
}