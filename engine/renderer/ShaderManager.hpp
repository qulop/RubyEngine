#pragma once

#include <types/TypeTraits.hpp>
#include <types/Singleton.hpp>

#include <sync/Mutex.hpp>

#include <misc/IManageCache.hpp>

#include "Shader.hpp"



namespace Ruby {
	class ShaderManager : IManageCache<Shader> {
		RUBY_DEFINE_SINGLETON(ShaderManager)
	
	public:
		RUBY_NODISCARD Opt<Shader&> GetFromCache(StringView name) override;
		RUBY_NODISCARD Opt<Shader&> GetFromLocalCache(StringView name) override;
		RUBY_NODISCARD Opt<Shader&> GetFromGlobalCache(StringView name) override;

        RUBY_NODISCARD bool IsInCache(StringView name) const override;
		RUBY_NODISCARD bool IsInLocalCache(StringView name) const override;
        RUBY_NODISCARD bool IsInGlobalCache(StringView name) const override;

        RUBY_NODISCARD void RemoveFromCache(StringView name) override;

        RUBY_NODISCARD void ClearAllCache() override;
        RUBY_NODISCARD void ClearLocalCache() override;

		RUBY_NODISCARD Path GetCacheDir() const override;

        void ChangeCacheDirectoryName(StringView newName) override;

	private:
		Sync::Mutex m_localCacheMutex;

		StringView m_cacheDirectoryName = "shaders";

		HashMap<hash_t, Shader> m_localCache;
	};

}