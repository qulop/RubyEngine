#pragma once

#include <types/TypeTraits.hpp>

#include <utility/Definitions.hpp>


namespace Ruby::Sync {
    class Thread {
    public:
        using IDType = std::thread::id;

    public:
        static void RegisterThisThreadAsMain();

        RUBY_NODISCARD static bool IsMainThread();

        RUBY_NODISCARD static IDType GetCurrentThreadID();

    private:
        static IDType s_mainThreadID;

        std::jthread m_threadHandle;
    };
}

namespace Ruby::ThisThread {
    RUBY_NODISCARD Sync::Thread::IDType GetID();

    RUBY_NODISCARD bool IsMainThread();
}