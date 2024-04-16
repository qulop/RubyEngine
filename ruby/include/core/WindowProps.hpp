#pragma once

#include <utility/Definitions.hpp>
#include <utility/TypeTraits.hpp>
#include <platform/Platform.hpp>

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>


namespace Ruby
{
    struct RUBY_API SizeStruct
    {
        i32 width = 0;
        i32 height = 0;

        SizeStruct() = default;

        SizeStruct(int width, int height) :
            width(width), height(height)
        {}

        explicit operator std::pair<int, int>() const
        { return std::make_pair(width, height); }
    };


    struct RUBY_API VideoStruct
    {
        RubyString title = "RubyEngine says hi!";
        i32 width = 0;
        i32 height = 0;
        bool isFullScreened = true;

        VideoStruct()
        { std::tie(width, height) = Platform::getScreenResolution(); }

        VideoStruct(RubyString&& title, int width, int height) :
            title(std::move(title)), width(width), height(height)
        {}

        explicit VideoStruct(RubyString&& title) :
            title(std::move(title))
        {}

        VideoStruct(int width, int height) :
            width(width), height(height)
        {}

        VideoStruct(RubyString&& title, bool isFullScreened) :
            title(std::move(title)), isFullScreened(isFullScreened)
        {}
    };
}