/*
    TODO:
        1) void RemoveListener(<...>)
        2) checking delegate in AddListener for existance
*/

#pragma once

#include <utility/Definitions.hpp>
#include <utility/Singleton.hpp>

#include "Event.hpp"

#include <utility/StdInc.hpp>


namespace Ruby
{
    namespace Details::Events
    {
        template<typename Tx, typename... Args>
        concept Callable = requires(Tx&& func, Event e)
        {
            std::is_invocable_v<Tx>;
            { g_NumberOfArguments_v<Tx> == 1 };
            { std::invoke(std::forward<Tx>(func), e) } -> std::same_as<void>;
        };
    }


    class EventManager : public Singleton<EventManager>
    {
        using Delegate = std::function<void(const Event&)>;
    public:
        DEFINE_SINGLETON(EventManager)       

        void Excite(const Event& event)
        {
            RUBY_LOCK_MUTEX(MutexType);

            if (m_bus.count(event.GetType()) == 0)
                return;

            for (auto&& delegate : m_bus[event.GetType()])
                std::invoke(delegate, event);
        }

        // If delegate not be present in listeners of specified type return true. False otherwise.
        template<Details::Events::Callable Func> 
        bool AddListener(EventType type, Func&& delegate)
        {
            LOCK_MUTEX(MutexType);
            Delegate newCallback = delegate;
            
            for (auto&& presentCallback : m_bus.at[type])
                if (GetFunctionAddress(newCallback) == GetFunctionAddress(presentCallback))
                    return false;

            m_bus[type].push_back(delegate); 
            return true;
        }

        template<Details::Events::Callable Func>
        bool RemoveListener(Func&& delegate)
        {
            return true;
        }

        void Clear(void)
        { m_bus.clear(); }

    private:

        template<typename... Args>
        size_t GetFunctionAddress(const std::function<void(Args...)>& fn)
        {
            using Signature = void(Args...);

            Signature** fnPtr = fn.template target<Signature*>();
            return (size_t)(*fnPtr);
        }    

    private:
        RubyHashMap<EventType, RubyVector<Delegate>> m_bus;
    };
}