#pragma once

#include <types/StdInc.hpp>


// Thread-Safe singleton
#define RUBY_DEFINE_SINGLETON(ClassName)    private:                                                \
                                                ClassName(void) = default;                          \
                                                                                                    \
                                            public:                                                 \
                                                ClassName(const ClassName&) = delete;               \
                                                ClassName(ClassName&&) = delete;                    \
                                                ClassName& operator=(const ClassName&) = delete;    \
                                                ClassName& operator=(ClassName&&) = delete;         \
                                                                                                    \
                                                static ClassName& GetInstance(void) {               \
                                                    static ClassName tmp;                           \
                                                    return tmp;                                     \
                                                }                                                   \


namespace Ruby {
    template<typename Derived>
    class Singleton {
    public:
        using MutexType = std::recursive_mutex;

        virtual ~Singleton() = default;

    protected:
        MutexType m_mutex;
    };
}