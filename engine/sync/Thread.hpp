#pragma once

#include <types/TypeTraits.hpp>

#include <utility/Definitions.hpp>


namespace Kiwi::Sync {
    class Thread {
    public:
        using IDType = std::thread::id;

    public:
        static void RegisterThisThreadAsMain();

        KIWI_NODISCARD static bool IsMainThread();

        KIWI_NODISCARD static IDType GetCurrentThreadID();

    private:
        static IDType s_mainThreadID;

        std::jthread m_threadHandle;
    };
}

namespace Kiwi::ThisThread {
    KIWI_NODISCARD Sync::Thread::IDType GetID();

    KIWI_NODISCARD bool IsMainThread();
}