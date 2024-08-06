#include "EventManager.hpp"


namespace Ruby {
    namespace Details::Events {
        _Listener::_Listener(IDType id, EventType eventType, Delegate&& delegate) :
            m_id(id),
            m_eventType(eventType),
            m_delegate(std::move(delegate))
        {}

        RUBY_NODISCARD _Listener::IDType _Listener::GetID() const noexcept {
            return m_id;
        }

        RUBY_NODISCARD EventType _Listener::GetEventType() const noexcept {
            return m_eventType;
        }

        void _Listener::Call(IEvent* event) const noexcept {
            try {
                std::invoke(m_delegate, event);
            }
            catch (...) {
                RUBY_ERROR("Listener::Call() : Failed to process invoke listener with ID {}. {}", m_id, event->ToString());
            }
        }
    }


    bool EventManager::RemoveListener(const ListenerType& listener) {
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

    void EventManager::Clear() {
        m_bus.clear();
    }
}