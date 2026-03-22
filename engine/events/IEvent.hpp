#pragma once

#include <utility/Definitions.hpp>
#include <utility/Enum.hpp>
#include <common/StdInc.hpp>


namespace Kiwi {
    KIWI_ENUM(EventType,
        KIWI_NONE_EVENT       = 0,
        KIWI_MOUSE_PRESSED    = (1 << 1),
        KIWI_MOUSE_RELEASED   = (1 << 2),
        KIWI_MOUSE_MOVED      = (1 << 3),
        KIWI_MOUSE_SCROLLED   = (1 << 4),
        KIWI_KEY_PRESSED      = (1 << 5),
        KIWI_KEY_RELEASED     = (1 << 6),
        KIWI_ANY_EVENT        = KIWI_MOUSE_PRESSED | KIWI_MOUSE_RELEASED | KIWI_MOUSE_MOVED |
                                KIWI_MOUSE_SCROLLED | KIWI_KEY_PRESSED | KIWI_KEY_RELEASED
    )


    KIWI_INTERFACE IEvent {
    public:
        KIWI_NODISCARD virtual EventType GetType() const = 0;
        KIWI_NODISCARD virtual String ToString() const = 0;

        virtual ~IEvent() = default;
    };


    namespace Details::Events {
        class _EventBase : public IEvent {
        public:
            KIWI_NODISCARD EventType GetType() const override {
                return m_type;
            }

            ~_EventBase() override = default;

        protected:
            explicit _EventBase(EventType type) :
                    m_type(type)
            {}

        protected:
            EventType m_type;
            EnumReflector m_reflector = EnumReflector::Create<EventType>();
        };
    }
}