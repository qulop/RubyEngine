#pragma once

#include <utility/Definitions.hpp>

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>


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


    struct RUBY_API VideoStruct
    {
        RubyString title = "RubyEngine says hi!";
        int width = 600;
        int height = 600;
        bool isFullScreened = true;

        VideoStruct(void) = default;

        VideoStruct(const RubyString& t, int w, int h) :
            title(t), width(w), height(h) 
        {}

        VideoStruct(const RubyString& t) :
            title(t)
        {}

        VideoStruct(int w, int h) :
            width(w), height(h)
        {}

        VideoStruct(const RubyString& t, bool isFS) :
            title(t), isFullScreened(isFS) 
        {}
    };
}