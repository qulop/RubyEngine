#pragma once

#include <common/meta/TypeTraits.hpp>
#include <common/filesystem/FileContent.hpp>
#include <common/filesystem/File.hpp>
#include <common/Definitions.hpp>
#include <common/Assert.hpp>

#include <sync/Mutex.hpp>



namespace Kiwi::Globals {
    constexpr StringView ROOT_CACHE_DIR = "cache";
}

namespace Kiwi::Traits {
    template<typename TCachedObject>
    struct CacheManagerTraits;
}

namespace Kiwi {
    template<typename TKey, std::copyable TCachedObject>
    class ALayeredCacheManagerBase {
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

            auto res = File::LoadFromFile(
                std::move(targetFilePath),
                (isBinaryFormat) ?
                    EFileOpenMode::READ | EFileOpenMode::BINARY :
                    EFileOpenMode::READ
            );

            return res.HasValue() ?
                Opt(res.GetValue()) :
                nullopt;
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

            auto saveRes = File::SaveInFile(std::move(targetPath), data, isBinaryFormat, overwrite);
            return saveRes.has_value();
        }

        void RemoveFromCache(StringView name) {
            RemoveFromLocalCache(name);

            KIWI_SCOPED_LOCK(m_globalCacheGuard);

            std::error_code ec;

            // TODO: Can fail
            std::filesystem::remove(std::move(GetPathToCachedFile(name)), ec);
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
        KIWI_NODISCARD StatusResult<EGeneralError> CreateGlobalCacheDirectoryOnInit() {
            KIWI_ASSERT_BASIC(!m_cacheDirectoryName.empty());

            if (!std::filesystem::create_directory(GetCacheDirAbsolutePath_NoLock())) {
                return Unexpected(Error{
                    .kind = EGeneralError::CREATE_FAIL,
                    .desc = std::format("failed to create a cache directory: {}", m_cacheDirectoryName),
                });
            }

            return {};
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