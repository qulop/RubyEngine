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
        using Delegate = std::function<void(Ptr<IEvent>)>;

        Listener(IDType id, EventType eventType, Delegate&& delegate) :
            m_id(id),
            m_eventType(eventType),
            m_delegate(std::move(delegate))
        {}

        RUBY_NODISCARD IDType GetID() const noexcept
        { return m_id; }

        RUBY_NODISCARD EventType GetEventType() const noexcept
        { return m_eventType; }

        void Call(const Ptr<IEvent>& event) const noexcept
        {
            try
            { std::invoke(m_delegate, event); }
            catch (...) {
                RUBY_ERROR("Listener::Call() : Failed to process invoke listener with ID {}. {}", m_id, event->ToString());
            }
        }

    private:
        IDType m_id = 0;
        EventType m_eventType;
        Delegate m_delegate;
    };


    class EventManager : public Singleton<EventManager>
    {
    public:
        using Delegate = std::function<void(IEvent*)>;

        DEFINE_SINGLETON(EventManager)

        template<typename E>
            requires std::derived_from<E, IEvent>
        void Excite(E event)
        {
            RUBY_LOCK_MUTEX(MutexType);
            if (m_bus.count(event.GetType()) == 0)
                return;

            for (auto&& listener : m_bus[event.GetType()])
                listener.Call(MakePtr<E>(event));
        }

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


    template<typename E>
        requires std::derived_from<E, IEvent>
    inline void exciteEvent(E&& event)
    { EventManager::GetInstance().Excite(std::forward<E>(event)); }

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