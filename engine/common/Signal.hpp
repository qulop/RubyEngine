#pragma once

#include <common/meta/TypeTraits.hpp>


namespace Kiwi {
    template<typename... Args>
    class Signal {
    public:
        using ListenerType = void(*)(Args...); 
    
    public:
        Signal() = default;

        Signal(ForwardList<ListenerType> listeners)
        : listeners(listeners)
        {}

        Signal(const Signal& other) 
        : listeners(other.listeners)
        {}

        Signal(Signal&& other)
        : listeners(std::move(other.listeners))
        {}
        
        ~Signal() = default;

    public:
        void AppendListener(ListenerType listener) {
            this->listeners.push_front(listener);
        }

        void Fire(Args&&... args) {
            for (auto& listener : this->listeners) {
                listener(args...);
            }
        }
        
    private:
        ForwardList<ListenerType> listeners;
    };
}