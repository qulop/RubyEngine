#pragma once

#include <types/TypeTraits.hpp>
#include <types/Singleton.hpp>

#include <sync/Mutex.hpp>

#include <misc/LayeredCacheManagerBase.hpp>

#include "Shader.hpp"


namespace Ruby {
	struct ShaderCacheEntry {
	public:
		static ShaderCacheEntry FromFileContent(const FileContent& fc);

	public:
		Vector<u32> spriVByteCode;


		ShaderCacheEntry() = default;

		explicit ShaderCacheEntry(const Vector<u32>& spvByteCode) :
			spriVByteCode(spvByteCode) 
		{}
		
		explicit ShaderCacheEntry(Vector<u32>&& spvByteCode) :
			spriVByteCode(std::move(spvByteCode))
		{}
	};
}

namespace Ruby::Traits {
	template<>
	struct CacheManagerTraits<ShaderCacheEntry> {
		static constexpr StringView defaultCacheDirName = "spir-v";
	};
}

namespace Ruby {
	class ShaderCacheManager : public LayeredCacheManagerBase<ShaderCacheEntry> {
		RUBY_DEFINE_SINGLETON(ShaderCacheManager)

	public:
		RUBY_NODISCARD static bool Init();

	public:
#pragma region LayeredCacheManagerBase Abstract Class Implementation
		RUBY_NODISCARD bool AddToCache(StringView name, const ShaderCacheEntry& data) override;


		RUBY_NODISCARD Opt<ShaderCacheEntry> GetFromLocalCache(StringView name) const override;

		RUBY_NODISCARD Opt<ShaderCacheEntry> GetOrAddToLocalCache(StringView name, const ShaderCacheEntry& data) override;

		RUBY_NODISCARD bool IsInLocalCache(StringView name) const override;

		RUBY_NODISCARD bool AddToLocalCache(StringView name, const ShaderCacheEntry& data) override;

		void RemoveFromLocalCache(StringView name) override;

		void ClearLocalCache() override;
#pragma endregion

	private:
		mutable Sync::Mutex m_localCacheGuard;

		HashMap<hash_t, ShaderCacheEntry> m_localCache;
	};

}