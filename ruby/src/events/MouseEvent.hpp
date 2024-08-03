#include "IEvent.hpp"


namespace Ruby {
    namespace Details::Events {
        // RUBY_MOUSE_PRESS && RUBY_MOUSE_RELEASED
        class _MouseButtonAction : public _EventBase {
        public:
            RUBY_NODISCARD RubyString ToString() const override {
                return std::format("{} : button = {}",
                                   m_reflector.GetByValue(m_type).GetFieldName(),
                                   button);
            }

        public:
            i32 button = -1;

        protected:
            _MouseButtonAction(i32 button, EventType type) :
                    _EventBase(type),
                    button(button)
            {}
        };


        // RUBY_MOUSE_MOVED && RUBY_MOUSE_SCROLLED
        class _MouseStateAction : public _EventBase {
        public:
            RUBY_NODISCARD RubyString ToString() const override {
                return std::format("(EventID){} : xoff = {}, yoff = {}", static_cast<i32>(m_type), xoff, yoff);
            }

        public:
            f64 xoff = -1;
            f64 yoff = -1;

        protected:
            _MouseStateAction(f64 xoff, f64 yoff, EventType type) :
                    _EventBase(type),
                    xoff(xoff),
                    yoff(yoff)
            {}
        };
    }



    class MousePressEvent final : public Details::Events::_MouseButtonAction {
    public:
        explicit MousePressEvent(i32 button) :
                _MouseButtonAction(button, RUBY_MOUSE_PRESSED)
            {}
    };


    class MouseReleaseEvent final : public Details::Events::_MouseButtonAction {
    public:
        explicit MouseReleaseEvent(i32 button) :
                _MouseButtonAction(button, RUBY_MOUSE_RELEASED)
            {}
    };



    class MouseMoveEvent : public Details::Events::_MouseStateAction {
    public:
        MouseMoveEvent(double xoff, double yoff) :
                _MouseStateAction(xoff, yoff, RUBY_MOUSE_MOVED)
            {}
    };


    class MouseScrollEvent : public Details::Events::_MouseStateAction {
    public:
        MouseScrollEvent(double xoff, double yoff) :
                _MouseStateAction(xoff, yoff, RUBY_MOUSE_SCROLLED)
            {}
    };
}