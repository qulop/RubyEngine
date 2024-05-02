#include "Event.hpp"


namespace Ruby
{
    namespace Details::Events
    {
        // RUBY_MOUSE_PRESS && RUBY_MOUSE_RELEASED
        class MouseButtonAction : public IEvent
        {
        public:
            RUBY_NODISCARD RubyString ToString() const override
            { return std::format("(EventID){} : button = {}", static_cast<i32>(m_type), button); }

        public:
            i32 button = -1;

        protected:
            MouseButtonAction(i32 button, EventType type) :
                IEvent(type),
                button(button)
            {}
        };


        // RUBY_MOUSE_MOVED && RUBY_MOUSE_SCROLLED
        class MouseStateAction : public IEvent
        {
        public:
            RUBY_NODISCARD RubyString ToString() const override
            { return std::format("(EventID){} : xoff = {}, yoff = {}", static_cast<i32>(m_type), xoff, yoff); }

        public:
            f64 xoff = -1;
            f64 yoff = -1;

        protected:
            MouseStateAction(double xoff, double yoff, EventType type) :
                IEvent(type),
                xoff(xoff),
                yoff(yoff)
            {}
        };
    }



    class MousePressEvent final : public Details::Events::MouseButtonAction
    {
    public:
        explicit MousePressEvent(i32 button) :
                MouseButtonAction(button, RUBY_MOUSE_PRESSED)
            {}
    };


    class MouseReleaseEvent final : public Details::Events::MouseButtonAction
    {
    public:
        explicit MouseReleaseEvent(i32 button) :
                MouseButtonAction(button, RUBY_MOUSE_RELEASED)
            {}
    };



    class MouseMoveEvent : public Details::Events::MouseStateAction
    {
    public:
        MouseMoveEvent(double xoff, double yoff) :
                MouseStateAction(xoff, yoff, RUBY_MOUSE_MOVED)
            {}
    };


    class MouseScrollEvent : public Details::Events::MouseStateAction
    {
    public:
        MouseScrollEvent(double xoff, double yoff) :
                MouseStateAction(xoff, yoff, RUBY_MOUSE_SCROLLED)
            {}
    };
}