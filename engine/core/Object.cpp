#include "Object.hpp"

#include <sync/Thread.hpp>



namespace Kiwi {
    AObject::SubsystemHolderType* AObject::s_subsystems = nullptr;

    const AObject* AObject::GetBasePtr() const {
        return this;
    }

    void AObject::RegisterSubsystem(ASubsystem* subsystem) {
        KIWI_ASSERT_BASIC(s_subsystems);
        KIWI_ASSERT(ThisThread::IsMainThread(), "You must call this function only from the main thread");

        s_subsystems->at(subsystem->GetType()).reset(subsystem);
    }

    void AObject::DestroySubsystem(Hash64 typeHash) {
        KIWI_ASSERT_BASIC(s_subsystems);
        KIWI_ASSERT(ThisThread::IsMainThread(), "You must call this function only from the main thread");

        auto it = s_subsystems->find(typeHash);
        if (it == std::ranges::end(*s_subsystems)) {
            return;
        }

        it->second.reset();
    }

    SharedPtr<ASubsystem> AObject::GetSubsystem(Hash64 typeHash) {
        KIWI_ASSERT_BASIC(s_subsystems);

        return s_subsystems->at(typeHash);
    }
}
