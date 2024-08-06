#pragma once

#include <utility/Definitions.hpp>
#include <utility/Singleton.hpp>

#include "KeyboardEvent.hpp"
#include "MouseEvent.hpp"

#include <utility/StdInc.hpp>


namespace Ruby {
    namespace Details::Events {
        class _Listener {
        public:
            using IDType = i64;
            using Delegate = std::function<void(IEvent*)>;

            _Listener(IDType id, EventType eventType, Delegate&& delegate);

            RUBY_NODISCARD IDType GetID() const noexcept;
            RUBY_NODISCARD EventType GetEventType() const noexcept;

            void Call(IEvent* event) const noexcept;

        private:
            IDType m_id = 0;
            EventType m_eventType;
            Delegate m_delegate;
        };
    }

    using EventListener = Details::Events::_Listener;


    class EventManager : public Singleton<EventManager> {
    public:
        using ListenerType = Details::Events::_Listener;
        DEFINE_SINGLETON(EventManager)

    public:
        bool RemoveListener(const ListenerType& listener);
        void Clear();

        template<typename EventType> requires std::derived_from<EventType, IEvent>
        void Excite(EventType&& event) {
            RUBY_LOCK_MUTEX(MutexType);
            if (m_bus.count(event.GetType()) == 0)
                return;

            for (auto&& listener: m_bus[event.GetType()])
                listener.Call(&event);
        }

        template<typename Func>
        const ListenerType& AddListener(EventType type, Func&& delegate) {
            RUBY_LOCK_MUTEX(MutexType);
            static ListenerType::IDType id = 0;

            m_bus[type].emplace_back(id, type, std::forward<Func>(delegate));
            ++id;

            return m_bus[type].back();
        }

    private:
        RubyHashMap<EventType, std::vector<ListenerType>> m_bus;
    };


    template<typename EventType>    requires std::derived_from<EventType, IEvent>
    inline void exciteEvent(EventType&& event) {
        EventManager::GetInstance().Excite(std::forward<EventType>(event));
    }

    template<typename Func>
    inline Details::Events::_Listener addEventListener(EventType type, Func&& delegate) {
        return EventManager::GetInstance().AddListener(type, std::forward<Func>(delegate));
    }

    template<typename Func, typename Instance>
    inline EventListener addEventListener(EventType type, Func&& delegate, Instance&& inst) {
        using Delegate = EventListener::Delegate;

        Delegate&& callback = std::bind(delegate, *inst, std::placeholders::_1);
        return EventManager::GetInstance().AddListener(type, std::move(callback));
    }

    inline bool removeEventListener(const EventListener& listener) {
        return EventManager::GetInstance().RemoveListener(listener);
    }
}