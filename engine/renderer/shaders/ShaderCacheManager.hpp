#pragma once

#include <types/TypeTraits.hpp>
#include <types/Singleton.hpp>

#include <sync/Mutex.hpp>

#include <misc/LayeredCacheManagerBase.hpp>

#include "Shader.hpp"


namespace Kiwi {
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

namespace Kiwi::Traits {
	template<>
	struct CacheManagerTraits<ShaderCacheEntry> {
		static constexpr StringView defaultCacheDirName = "spir-v";
	};
}

namespace Kiwi {
	class ShaderCacheManager : public ALayeredCacheManagerBase<Hash64, ShaderCacheEntry> {
		KIWI_DEFINE_SINGLETON(ShaderCacheManager)

	public:
		KIWI_NODISCARD static bool Init();

	public:
		KIWI_NODISCARD bool AddToCache(Hash64 key, const ShaderCacheEntry& data) override;

		KIWI_NODISCARD Opt<ShaderCacheEntry> GetFromLocalCache(Hash64 key) const override;

		KIWI_NODISCARD Opt<ShaderCacheEntry> GetOrAddToLocalCache(Hash64 key, const ShaderCacheEntry& data) override;

		KIWI_NODISCARD bool IsInLocalCache(Hash64 key) const override;

		KIWI_NODISCARD bool AddToLocalCache(Hash64 key, const ShaderCacheEntry& data) override;

		KIWI_NODISCARD Opt<ShaderCacheEntry> TryToFindCachedShader(Hash64 hashedShaderSource);
		
		void RemoveFromLocalCache(Hash64 key) override;

		void ClearLocalCache() override;

	private:
		mutable Sync::Mutex m_localCacheGuard;

		// TODO: Add ability to store `Hash<T>` in `HashMap`
		HashMap<u64, ShaderCacheEntry> m_localCache;
	};

}