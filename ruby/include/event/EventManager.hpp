/*
    TODO:
        1) void RemoveListener(<...>)
        2) checking delegate in AddListener for existance
*/

#pragma once

#include "../utility/Definitions.hpp"

#include "Event.hpp"

#include <type_traits>
#include <functional>
#include <variant>


namespace Ruby
{
    namespace EventDetails
    {
        template<typename Tx, typename... Args>
        concept Callable = requires(Tx&& func, Event e, Args...)
        {
            std::is_invocable_v<Tx>;
            { std::invoke(std::forward<Tx>(func), e) } -> std::same_as<void>;
        };
    }



    class EventManager
    {
    public:
        using Delegate = std::function<void(Event&&)>;

               
        EventManager(const EventManager&)               = delete;
        EventManager(EventManager&&)                    = delete;
        EventManager& operator=(const EventManager&)    = delete;
        EventManager& operator=(EventManager&&)         = delete;
        

        // template<typename Tx>
        void Excite(Event&& event)
        {
            if (m_bus.count(event.GetType()) == 0)
                return;

            for (auto& delegate : m_bus[event.GetType()])
                std::invoke(delegate, std::move(event));
        }

        // - if delegate not be present in listeners of specified type return true
        //    false otherwise
        template<EventDetails::Callable Func> 
        bool AddListener(EventType type, Func&& delegate)
        {
            // RUBY_ASSERT_VAR bool isCorrectParam = CheckCallbackParameter<Tx>(type);
            // RUBY_ASSERT(isCorrectParam && "In the transferred handler of event parameter type doesn't match with event type.");

        
            m_bus[type].push_back(delegate); 
            return true;
        }

    
        // template<typename Tx>
            // requires std::is_base_of_v<Event, Tx>
        // bool RemoveListener()

    private:
        EventManager(void) = default;

        // Compare two callback-function for equal their addresses
        bool IsCallbacksEqual(size_t newCallbackAddr, const Delegate& delegate)
        {
            // auto comparer = [this, &newCallbackAddr](const auto& existingCallback) -> bool
            // {
            //     return newCallbackAddr == GetFnAddress(existingCallback);
            // };

            // return std::visit(comparer, delegate);
        }


        template<typename... Args>
        size_t GetFnAddress(const std::function<void(Args...)>& fn)
        {
            typedef void(Signature)(Args...);

            Signature** fnPtr = fn.template target<Signature*>();
            return (size_t)(*fnPtr);
        }

        template<typename Tx>
        bool CheckCallbackParameter(EventType type) const
        {
            // RUBY_ASSERT(type != RB_NONE_EVENT && "EventType cant be NONE_EVENT(absent)");

            // switch (type)
            // {
            // case RB_MOUSE_PRESSED:
            // case RB_MOUSE_RELEASED:
            //     return std::is_same_v<Tx, MousePressEvent>;

            // case RB_MOUSE_MOVED:
            //     return std::is_same_v<Tx, MouseMoveEvent>;
            
            // default:
            //     return false;
            // }          
        }
    

    private:
        friend inline EventManager& getEventManager(void);

        RubyHashMap<EventType, RubyVector<Delegate>> m_bus;
    };


    inline EventManager& getEventManager(void)
    {
        static EventManager mng;

        return mng;
    }
}