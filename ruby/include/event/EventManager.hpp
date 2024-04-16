#pragma once

#include <utility/Definitions.hpp>
#include <utility/Singleton.hpp>

#include "KeyboardEvent.hpp"
#include "MouseEvent.hpp"

#include <utility/StdInc.hpp>


namespace Ruby
{
    namespace Details::Events
    {
        using Delegate = std::function<void(IEvent*)>;

        template<typename Tx, typename... Args>
        concept Callable = requires(Tx&& func, IEvent e)
        {
            std::is_invocable_v<Tx>;
            { g_NumberOfArguments_v<Tx> == 1 };
            { std::invoke(std::forward<Tx>(func), e) } -> std::same_as<void>;
        };
    }


    class Listener
    {
    public:
        using IDType = i64;

        Listener(IDType id, EventType eventType, std::function<void(IEvent*)>&& delegate) :
            m_id(id),
            m_eventType(eventType),
            m_delegate(std::move(delegate))
        {}

        RUBY_NODISCARD IDType GetID() const noexcept
        { return m_id; }

        RUBY_NODISCARD EventType GetEventType() const noexcept
        { return m_eventType; }

        bool Call(IEvent* event) const noexcept
        {
            try
            { std::invoke(m_delegate, event); }
            catch (...)
            {
                RUBY_ERROR("Listener::Call() : Failed to process invoke listener with ID {}. {}", m_id, event->ToString());
                return false;
            }

            return true;
        }

    private:
        IDType m_id = 0;
        EventType m_eventType;
        std::function<void(IEvent*)> m_delegate;
    };


    class EventManager : public Singleton<EventManager>
    {
    public:
        using Delegate = std::function<void(IEvent*)>;

        DEFINE_SINGLETON(EventManager)

        template<typename EType>
            requires std::derived_from<EType, IEvent>
        void Excite(EType event)
        {
            RUBY_LOCK_MUTEX(MutexType);
            if (m_bus.count(event.GetType()) == 0)
                return;

            for (auto&& listener : m_bus[event.GetType()])
                listener.Call(&event);
        }

        // If delegate not be present in listeners of specified type return true. False otherwise.
        template<typename Func>
        Listener AddListener(EventType type, Func&& delegate)
        {
            RUBY_LOCK_MUTEX(MutexType);
            static Listener::IDType id = 0;

            Listener listener{ id, type, std::forward<Func>(delegate) };
            m_bus[type].push_back(listener);
            ++id;

            return listener;
        }

        bool RemoveListener(const Listener& listener)
        {
            RUBY_LOCK_MUTEX(MutexType);
            auto&& listenersIt = m_bus.find(listener.GetEventType());
            if (listenersIt == m_bus.end())
                return false;

            auto&& it = std::remove_if(listenersIt->second.begin(), listenersIt->second.end(),
                           [listener](auto&& containedListener) {
                                    return (containedListener.GetID() == listener.GetID());
            });

            return !(it == std::end(listenersIt->second));
        }

        void Clear()
        { m_bus.clear(); }

    private:
        RubyHashMap<EventType, std::vector<Listener>> m_bus;
    };


    template<typename EType>
        requires std::derived_from<EType, IEvent>
    inline void exciteEvent(EType event)
    { EventManager::GetInstance().Excite(event); }

    template<typename Func>
    inline Listener addEventListener(EventType type, Func&& delegate)
    { return EventManager::GetInstance().AddListener(type, std::forward<Func>(delegate)); }

    template<typename Func, typename Instance>
    inline Listener addEventListener(EventType type, Func&& delegate, Instance&& inst)
    {
        EventManager::Delegate callback = std::bind(delegate, *inst, std::placeholders::_1);

        return EventManager::GetInstance().AddListener(type, std::move(callback));
    }

    inline bool removeEventListener(const Listener& listener)
    { return EventManager::GetInstance().RemoveListener(listener); }
}