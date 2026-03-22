#pragma once

#include <common/StdInc.hpp>
#include <common/Concepts.hpp>


#define KIWI_DEFINE_SINGLETON(ClassName)    private:                                                    \
                                                ClassName(void) = default;                              \
                                                                                                        \
                                            public:                                                     \
                                                ClassName(const ClassName&) = delete;                   \
                                                ClassName(ClassName&&) = delete;                        \
                                                ClassName& operator=(const ClassName&) = delete;        \
                                                ClassName& operator=(ClassName&&) = delete;             \
                                                                                                        \
                                                KIWI_DEPRECATED static ClassName& GetInstance(void) {   \
                                                    static ClassName tmp;                               \
                                                    return tmp;                                         \
                                                }                                                       \


namespace Kiwi {
    template<typename Derived>
    class Singleton {
    public:
        using DerivedType = Derived;
        using MutexType = std::recursive_mutex;

    public:
        virtual void OnSingletonUp() {}
        virtual void OnSingletonDown() {}


        virtual ~Singleton() = default;

    protected:
        MutexType m_mutex;
    };
}