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
            { return std::format("{} : button = {}", m_type.GetFieldName(), button); }

        public:
            i16 button = -1;

        protected:
            MouseButtonAction(i16 button, const ENUM_FIELD& type) :
                IEvent(type),
                button(button)
            {}
        };


        // RUBY_MOUSE_MOVED && RUBY_MOUSE_SCROLLED
        class MouseStateAction : public IEvent
        {
        public:
            f64 xoff = -1;
            f64 yoff = -1;


        protected:
            MouseStateAction(double xoff, double yoff, const ENUM_FIELD& type) :
                IEvent(type),
                xoff(xoff),
                yoff(yoff)
            {}
        };
    }



    class MousePressEvent : public Details::Events::MouseButtonAction
    {
    public:
        explicit MousePressEvent(i16 button) :
                MouseButtonAction(button, m_reflector.GetByKey("RUBY_MOUSE_PRESSED"))
            {}
    };


    class MouseReleaseEvent : public Details::Events::MouseButtonAction
    {
    public:
        explicit MouseReleaseEvent(i16 button) :
                MouseButtonAction(button, m_reflector.GetByKey("RUBY_MOUSE_RELEASED"))
            {}
    };



    class MouseMoveEvent : public Details::Events::MouseStateAction
    {
    public:
        MouseMoveEvent(double xoff, double yoff) :
                MouseStateAction(xoff, yoff, m_reflector.GetByKey("RUBY_MOUSE_MOVED"))
            {}
    };


    class MouseScrollEvent : public Details::Events::MouseStateAction
    {
    public:
        MouseScrollEvent(double xoff, double yoff) :
                MouseStateAction(xoff, yoff, m_reflector.GetByKey("RUBY_MOUSE_SCROLLED"))
            {}
    };
}