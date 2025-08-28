#pragma once

#include <types/TypeTraits.hpp>
#include <utility/Definitions.hpp>


namespace Ruby::Globals {
    extern StringView ROOT_CACHE_DIR = "cache";
}

namespace Ruby {
    template<typename T>
    RUBY_INTERFACE IManageCache {
        virtual RUBY_NODISCARD Opt<T&> GetFromCache(StringView name) = 0;
        virtual RUBY_NODISCARD Opt<T&> GetFromLocalCache(StringView name) = 0;
        virtual RUBY_NODISCARD Opt<T&> GetFromGlobalCache(StringView name) = 0;

        virtual RUBY_NODISCARD bool IsInCache(StringView name) const = 0;
        virtual RUBY_NODISCARD bool IsInLocalCache(StringView name) const = 0;
        virtual RUBY_NODISCARD bool IsInGlobalCache(StringView name) const = 0;

        virtual void RemoveFromCache(StringView name) = 0;

        virtual void ClearAllCache() = 0;
        virtual void ClearLocalCache() = 0;

        virtual RUBY_NODISCARD Path GetCacheDir() const = 0;

        virtual void ChangeCacheDirectoryName(StringView newName) = 0;

        virtual ~IManageCache() = default;
    };
}