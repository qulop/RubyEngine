#pragma once

#include "Core.hpp"

// OpenGL(Glad) && GLFW
#include <glad/glad.h>

#define GLFW_INCLUDE_NONE
#include <glfw/include/GLFW/glfw3.h>
// ----------


namespace Ruby
{
    struct RUBY_API SizeStruct
    {
        int height = 0;
        int width = 0;

        SizeStruct(void) = default;

        SizeStruct(int h, int w) :
            height(h), width(w)
        {}
    };


    inline SizeStruct RUBY_API getScreenResolution(void)
    {
        const GLFWvidmode* tmp = glfwGetVideoMode(glfwGetPrimaryMonitor()); 
        
        return SizeStruct{ tmp->height, tmp->width };
    }


    struct RUBY_API VideoAttr
    {
        std::string title = "RubyEngine says hi!";
        int width = 100;
        int height = 100;

        bool isFullScreened = false;
        bool isResizable = true;

        VideoAttr(void) = default;

        VideoAttr(const std::string& t, int w, int h) :
            title(t), width(w), height(h) 
        {}

        VideoAttr(const std::string& t) :
            title(t)
        {}

        VideoAttr(int w, int h) :
            width(w), height(h)
        {}
    };
}