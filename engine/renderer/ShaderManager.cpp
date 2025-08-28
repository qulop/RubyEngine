#include "ShaderManager.hpp"

#include <utility/Cast.hpp>

#include <types/Logger.hpp>

#include <ranges>


namespace StdFileSystem = std::filesystem;


namespace {
    StdFileSystem::directory_iterator getCompiledShaderFiles() {
        auto&& cacheDir = std::move(Ruby::ShaderManager::GetInstance().GetCacheDir());

        return StdFileSystem::directory_iterator(cacheDir);
    }
}

namespace Ruby {
    Opt<Shader&> ShaderManager::GetFromCache(StringView name) {
        if (auto optRes = GetFromLocalCache(name); optRes) {
            return optRes;
        }

        return GetFromGlobalCache(name);
    }

    Opt<Shader&> ShaderManager::GetFromLocalCache(StringView name) {
        auto hashToFind = Cast::To<hash_t>(std::stoull(std::string{ name }, nullptr, 16));

        std::scoped_lock _{ m_localCacheMutex };
        if (!m_localCache.contains(hashToFind)) {
            return nullopt;
        }

        return m_localCache.at(hashToFind);
    }

    Opt<Shader&> ShaderManager::GetFromGlobalCache(StringView name) {

    }

    bool ShaderManager::IsInCache(StringView name) const {
        return IsInLocalCache(name) || IsInGlobalCache(name);
    }

    bool ShaderManager::IsInLocalCache(StringView name) const {
        return GetFromLocalCache(name).has_value();
    }

    bool ShaderManager::IsInGlobalCache(StringView name) const {
        for (const auto& entry : getCompiledShaderFiles() |
            std::views::filter([](auto&& e) { return !StdFileSystem::is_regular_file(e); }))
        {
            if (entry.path().stem().string() == name) {
                return true;
            };
        }

        return false;
    }

    void ShaderManager::RemoveFromCache(StringView name) {
        auto h = Cast::To<hash_t>(std::stoull(std::string{ name }, nullptr, 16));

        std::scoped_lock _{ m_localCacheMutex };

        m_localCache.erase(h);
        
        std::error_code ec;
        if (!StdFileSystem::remove(GetCacheDir() / name, ec)) {
            RUBY_ERROR("ShaderManager::RemoveFromCache() : Failed to remove a file {} - {}", name, ec.message());
        }
    }

    void ShaderManager::ClearAllCache() {
        ClearLocalCache();

        StdFileSystem::remove_all(std::move(GetCacheDir()));
    }

    void ShaderManager::ClearLocalCache() {
        std::scoped_lock _{ m_localCacheMutex };

        m_localCache.clear();
    }

    Path ShaderManager::GetCacheDir() const {
        std::scoped_lock _{ m_localCacheMutex };

        return StdFileSystem::absolute(Path{ Globals::ROOT_CACHE_DIR }) / m_cacheDirectoryName;
    }

    void ShaderManager::ChangeCacheDirectoryName(StringView newName) {
        std::scoped_lock _{ m_localCacheMutex };

        m_cacheDirectoryName = newName;
    }

}