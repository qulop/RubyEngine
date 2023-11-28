// #include "EventManager.hpp"


// namespace Ruby
// {
//     bool EventManager::IsCallbacksEqual(size_t newCallbackAddr, const Delegate& delegate)
//     {
//         auto comparer = [this, &newCallbackAddr](const auto& existingCallback) -> bool
//         {
//             return false;   // newCallbackAddr == GetFnAddress(existingCallback);
//         };

//         return std::visit(comparer, delegate);
//     }



//     EventManager& GetManager(void)
//     {
//         static EventManager mng;
        
//         return mng;
//     }

// }