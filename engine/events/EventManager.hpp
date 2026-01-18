/*
    TODO:

    Need to rework the event system.
    
    First of all, the event system using strictly defined event types, such as `MousePressEvent`, `MouseReleaseEvent` and so on
    So, we need to create more extensible system, where developers can define their own event types

    Then, `EventListener` using `i64` as the ID type. I suppose, it would be much more efficient to use GUID? 
    But, maybe `i64` more preffereble, because each GUID needs some overhead for generation, while `i64` just using incrementation 
    in the `EventManager::AddListener()` function

    And then, as plesent addition, it would be cool to create some sort of immidiate event handling. Something like this:

    ```
    KeyboardKeyEvent keyboardEvent;
    if (auto keyboardEvent = isKeyboardKeyPressed(); keyboardEvent) {
        // Event handling here
    }
    ```
*/


#pragma once

#include <utility/Definitions.hpp>
#include <utility/Assert.hpp>

#include <types/Singleton.hpp>
#include <types/Concepts.hpp>
#include <types/StdInc.hpp>

#include <core/Object.hpp>

#include <platform/io/SystemConsole.hpp>

#include "KeyboardEvent.hpp"
#include "MouseEvent.hpp"


namespace Kiwi {
    class EventListener {
    public:
        using IDType = i64;
        using Delegate = std::function<void(IEvent*)>;

    public:
        EventListener() = default;
        EventListener(IDType id, EventType eventType, Delegate&& delegate);

        KIWI_NODISCARD IDType GetID() const noexcept;
        KIWI_NODISCARD EventType GetEventType() const noexcept;

        void Call(IEvent* event) const noexcept;

    private:
        IDType m_id = KIWI_UNDEFINED_ID;
        EventType m_eventType;
        Delegate m_delegate;
    };


    class EventSubsystem : public ASubsystem {
        KIWI_CREATE_OBJECT(EventSubsystem)

    private:
        using Super = ASubsystem;
        using KeyType = EventType;
        using ValueType = Vector<EventListener>;

    public:
        EventSubsystem() = default;

    public:
        bool Init() override {
            Super::Init();

            return true;
        }

        KIWI_NODISCARD size_t GetNumberOfListenersForEvent(EventType type) const {
            return (m_bus.find(type) != m_bus.end()) ? m_bus.at(type).size() : 0;
        }

        KIWI_NODISCARD size_t GetTotalNumberOfListeners() const {
            return std::accumulate(m_bus.begin(), m_bus.end(), (size_t)0, [](size_t acc, const auto& pair) {
                const auto& [eventType, vec] = pair;
                return acc + vec.size();
            });
        }

        KIWI_NODISCARD size_t Size() const {
            return m_bus.size();
        }

        template<typename EventType>
            requires std::derived_from<EventType, IEvent>
        void Excite(EventType&& event) {
            KIWI_ASSERT(m_bus.find(event.GetType()) != m_bus.end(), "First you need to initialize the EventManager!");

            KIWI_SCOPED_LOCK(m_mutex);
            if (m_bus.find(event.GetType()) == m_bus.end())
                return;

            for (auto&& listener: m_bus[event.GetType()])
                listener.Call(&event);
        }

        template<Concepts::Callable Func>
        KIWI_NODISCARD const EventListener& AddListener(EventType type, Func&& delegate) {
            KIWI_ASSERT(m_bus.find(type) != m_bus.end(), "First you need to initialize the EventManager!");

            KIWI_SCOPED_LOCK(m_mutex);
            static EventListener::IDType id = 0;

            // TODO: [NOTE] - This code doesn't take into account our allocated memory on Init() step
            m_bus.at(type).emplace_back(id, type, std::forward<Func>(delegate));
            ++id;

            KIWI_ASSERT_BASIC(m_bus.at(type).back().GetID() != KIWI_UNDEFINED_ID);
            return m_bus.at(type).back();
        }

        KIWI_NODISCARD bool RemoveListener(const EventListener& listener) {
            KIWI_ASSERT(m_bus.find(listener.GetEventType()) != m_bus.end(), "First you need to initialize the EventManager!");

            KIWI_SCOPED_LOCK(m_mutex);
            auto&& listenersIt = m_bus.find(listener.GetEventType());
            if (listenersIt == m_bus.end())
                return false;

            auto&& it = std::remove_if(listenersIt->second.begin(), listenersIt->second.end(),
                                       [&listener](const auto& containedListener) {
                                           return (containedListener.GetID() == listener.GetID());
                                       });

            return !(it == std::end(listenersIt->second));
        }

        void DeInit() override {
            m_bus.clear();
        }

    private:
        Sync::Mutex m_mutex;
        HashMap<KeyType, ValueType> m_bus;
    };
}
