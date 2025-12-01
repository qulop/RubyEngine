#include "Thread.hpp"


namespace Kiwi::Sync {
    Thread::IDType Thread::s_mainThreadID = Thread::IDType();


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

namespace Kiwi::ThisThread {
    Sync::Thread::IDType GetID() {
        return Sync::Thread::GetCurrentThreadID();
    }

    bool IsMainThread() {
        return Sync::Thread::IsMainThread();
    }
}
