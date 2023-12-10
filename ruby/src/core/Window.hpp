#pragma once

#include <utility/Definitions.hpp>
#include <utility/Logger.hpp>
#include <event/Event.hpp>
#include "WindowProps.hpp"


namespace Ruby
{

    class RUBY_API Window
    {
    public:
        Window(VideoAttr& va);

        // Update window state and return flag from glfwWindowShouldClose();
        bool Update(void);

        void PollEvents(void);

        SizeStruct GetSize(void) const;

        SizeStruct GetRealSize(void) const;

        ~Window(void) = default;

    private:
        void Init(VideoAttr& wa);

        void SetupCallbacks(void);

    private:
        std::shared_ptr<GLFWwindow> m_window;
    };
}