#pragma once

#include "Core.hpp"
#include "Logger.hpp"
#include "WindowProps.hpp"
// #include <event/Event.hpp>

#include <array>


namespace Ruby
{

    class RUBY_API Window
    {
    public:
        Window(VideoAttr& va);

        // Update window state and return flag from glfwWindowShouldClose();
        bool Update(void);

        SizeStruct GetSize(void) const;

        SizeStruct GetRealSize(void) const;

        // coords: { x1, y1, x2, y2, x3, y3 }
        void DrawTriangle(void);

        ~Window(void);

    private:
        void Init(VideoAttr& wa);

        // void SetupGLFWCallbacks(void);

    private:
        GLFWwindow* m_window;
    };
}