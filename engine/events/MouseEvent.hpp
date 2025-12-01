#include "IEvent.hpp"


namespace Kiwi {
    namespace Details::Events {
        // KIWI_MOUSE_PRESS && KIWI_MOUSE_RELEASED
        class _MouseButtonAction : public _EventBase {
        public:
            KIWI_NODISCARD String ToString() const override {
                return std::format("{} : button = {}",
                                   m_reflector.GetByValue(m_type).GetFieldName(),
                                   button);
            }

        public:
            i32 button = -1;

        protected:
            explicit _MouseButtonAction(EventType type, i32 button) :
                    _EventBase(type),
                    button(button)
            {}
        };


        // KIWI_MOUSE_MOVED && KIWI_MOUSE_SCROLLED
        class _MouseStateAction : public _EventBase {
        public:
            KIWI_NODISCARD String ToString() const override {
                return std::format("{} : xoff = {}, yoff = {}",
                                   m_reflector.GetByValue(m_type).GetFieldName(),
                                   xoff,
                                   yoff);
            }

        public:
            f64 xoff = -1;
            f64 yoff = -1;

        protected:
            explicit _MouseStateAction(EventType type, f64 xoff, f64 yoff) :
                    _EventBase(type),
                    xoff(xoff),
                    yoff(yoff)
            {}
        };
    }



    class MousePressEvent final : public Details::Events::_MouseButtonAction {
    public:
        MousePressEvent(i32 button) :   // NOLINT
                _MouseButtonAction(KIWI_MOUSE_PRESSED, button)
            {}
    };


    class MouseReleaseEvent final : public Details::Events::_MouseButtonAction {
    public:
        MouseReleaseEvent(i32 button) :     // NOLINT
                _MouseButtonAction(KIWI_MOUSE_RELEASED, button)
            {}
    };



    class MouseMoveEvent : public Details::Events::_MouseStateAction {
    public:
        MouseMoveEvent(double xoff, double yoff) :
                _MouseStateAction(KIWI_MOUSE_MOVED, xoff, yoff)
            {}
    };


    class MouseScrollEvent : public Details::Events::_MouseStateAction {
    public:
        MouseScrollEvent(double xoff, double yoff) :
                _MouseStateAction(KIWI_MOUSE_SCROLLED, xoff, yoff)
            {}
    };
}