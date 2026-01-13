#include "Object.hpp"

#include <sync/Thread.hpp>

#include <core/LogSubsystem.hpp>



namespace Kiwi {
    AObject::SubsystemHolderType* AObject::s_subsystems = nullptr;

    const AObject* AObject::GetObjectBase() const {
        return this;
    }

    void AObject::RegisterSubsystem(ASubsystem* subsystem) {
        KIWI_ASSERT_BASIC(s_subsystems);
        KIWI_ASSERT(ThisThread::IsMainThread(), "You must call this function only from the main thread");

        s_subsystems->operator[](subsystem->GetType()).reset(subsystem);
    }

    void AObject::LogImpl(ELogLevel lvl, const String& msg) const {
        KIWI_ASSERT_BASIC(AObject::IsSubsystemPresent<LogSubsystem>());

        GetSubsystem<LogSubsystem>()->Log(lvl, msg);
    }



    bool ASubsystem::Init() {
        KIWI_ASSERT(ThisThread::IsMainThread(), "A subsystem must be initialized only from a main thread");

        return true;
    }

    void ASubsystem::DeInit() {
        KIWI_ASSERT(ThisThread::IsMainThread(), "A subsystem must be deinitialized only from a main thread");
    }
}
