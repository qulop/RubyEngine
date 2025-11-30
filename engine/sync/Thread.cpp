#include "Thread.hpp"


namespace Ruby::Sync {
    void Thread::RegisterThisThreadAsMain() {

        s_mainThreadID = GetCurrentThreadID();
    }

    bool Thread::IsMainThread() {
        return GetCurrentThreadID() == s_mainThreadID;
    }

    Thread::IDType Thread::GetCurrentThreadID() {
        return std::this_thread::get_id();
    }
}

namespace Ruby::ThisThread {
    Sync::Thread::IDType GetID() {
        return Sync::Thread::GetCurrentThreadID();
    }

    bool IsMainThread() {
        return Sync::Thread::IsMainThread();
    }
}
