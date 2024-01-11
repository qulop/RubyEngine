/*
    TODO:
        1) void RemoveListener(<...>)
        2) checking delegate in AddListener for existance
*/

#pragma once

#include <core/Window.hpp>
#include <utility/Definitions.hpp>

#include "RubyEvents.hpp"

#include <type_traits>
#include <functional>
#include <variant>


namespace Ruby
{
    class EventManager;

    EventManager& getEventManager(void);


    class EventManager
    {
    public:
    // Announcements
        using Delegate = std::variant<
                            std::function<void(MousePressEvent&)>, 
                            std::function<void(MouseMoveEvent&)>>; 
        
               
        EventManager(const EventManager&) = delete;
        EventManager(EventManager&&) = delete;
        EventManager& operator=(const EventManager&) = delete;
    // --------

    // Templates implementation
        template<typename Tx>
            requires std::is_base_of_v<Event, Tx>
        void Excite(Tx event)
        {
            if (m_bus.count(event.GetType()) == 0)
                return;

            auto unpacker = [&event](const auto& callback) -> void
            {
                using RecivedType = std::decay_t<decltype(callback)>;
                using ExpectedType = std::function<void(Tx&)>;

                if constexpr (std::is_same_v<RecivedType, ExpectedType>)
                    callback(event); 
            };
            
            for (auto& delegate : m_bus[event.GetType()])
                std::visit(unpacker, delegate);
        }

        // - if delegate not be present in listeners of specified type return true
        //    false otherwise
        template<typename Tx> 
            requires std::is_base_of_v<Event, Tx>
        bool AddListener(EventType type, const std::function<void(Tx&)>& delegate)
        {
            RUBY_ASSERT_VAR bool isCorrectParam = CheckCallbackParameter<Tx>(type);
            RUBY_ASSERT(isCorrectParam && "In the transferred handler of event parameter type doesn't match with event type.");

        
            m_bus[type].push_back(delegate); 
            return true;
        }
    // ------------

    private:
    // Announcements
        EventManager(void) = default;

        // Compare two callback-function for equal their addresses
        // bool IsCallbacksEqual(size_t newCallbackAddr, const Delegate& delegate);
    // ------------


    // Templates implementation
        template<typename... Args>
        size_t GetFnAddress(const std::function<void(Args...)>& fn)
        {
            typedef void(Signature)(Args...);

            Signature** fnPtr = fn.template target<Signature*>();
            return (size_t)(*fnPtr);
        }

        template<typename Tx>
        constexpr bool CheckCallbackParameter(EventType type) const
        {
            RUBY_ASSERT(type != RB_NONE_EVENT && "EventType cant be NONE_EVENT(absent)");

            switch (type)
            {
            case RB_MOUSE_PRESSED:
            case RB_MOUSE_RELEASED:
                return std::is_same_v<Tx, MousePressEvent>;

            case RB_MOUSE_MOVED:
                return std::is_same_v<Tx, MouseMoveEvent>;
            
            default:
                return false;
            }          
        }
    
    // -------------

    private:
        friend EventManager& getEventManager(void);

        RubyHashMap<EventType, RubyVector<Delegate>> m_bus;
    };
}