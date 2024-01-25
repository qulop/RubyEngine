#pragma once

#include <utility/Definitions.hpp>
#include <utility/Logger.hpp>
#include <event/RubyEvents.hpp>
#include <render/shaders/ShaderProgram.hpp>
#include "WindowProps.hpp"

#include <iostream>


namespace Ruby
{

    class RUBY_API Window
    {
    public:
        explicit Window(VideoAttr& va);

        // Update window state and return flag from glfwWindowShouldClose();
        bool Update(void);

        void PollEvents(void);

        SizeStruct GetSize(void) const;

        SizeStruct GetRealSize(void) const;

        ~Window();

    private:
        void Init(VideoAttr& wa);

        void SetupCallbacks(void);

    private:
        GLFWwindow* m_window;
    };
}