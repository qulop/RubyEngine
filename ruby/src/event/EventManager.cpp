#include "EventManager.hpp"


namespace Ruby
{
    EventManager& EventManager::Get(void) 
    {
        static EventManager instance;
        return instance;
    }


    bool EventManager::IsCallbacksEqual(size_t newCallbackAddr, const Delegate& delegate)
    {
        auto comparer = [this, &newCallbackAddr](const auto& existingCallback) -> bool
        {
            return false;   // newCallbackAddr == GetFnAddress(existingCallback);
        };

        return std::visit(comparer, delegate);
    }

}