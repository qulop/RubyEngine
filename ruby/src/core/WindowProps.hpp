#pragma once

#include <utility/Definitions.hpp>
#include <utility/TypeTraits.hpp>
#include <platform/Platform.hpp>

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>


namespace Ruby {
    struct RUBY_API SizeStruct {
        i32 width = 0;
        i32 height = 0;

        SizeStruct() = default;

        SizeStruct(i32 width, i32 height) :
            width(width), height(height)
        {}

        operator std::pair<i32, i32>() const {
            return std::make_pair(width, height);
        }
    };


    struct RUBY_API VideoStruct {
        RubyString title = "RubyEngine application";
        i32 width = 0;
        i32 height = 0;
        bool isFullScreened = true;

        VideoStruct() {
            std::tie(width, height) = Platform::getScreenResolution();
        }

        VideoStruct(VideoStruct&& other) noexcept {
            *this = std::move(other);
        }

        VideoStruct(const VideoStruct& other) noexcept {
            *this = other;
        }

        VideoStruct(RubyString&& title, i32 width, i32 height) :
            title(std::move(title)), width(width), height(height)
        {}

        explicit VideoStruct(RubyString&& title) :
            title(std::move(title))
        {}

        VideoStruct(i32 width, i32 height) :
            width(width), height(height)
        {}

        VideoStruct(RubyString&& title, bool isFullScreened) :
            title(std::move(title)), isFullScreened(isFullScreened)
        {}

        VideoStruct& operator=(VideoStruct&& other) noexcept {
            if (this == &other)
                return *this;

            title = std::move(other.title);
            width = other.width;
            height = other.height;
            isFullScreened = other.isFullScreened;;

            return *this;
        }

        VideoStruct& operator=(const VideoStruct& other) noexcept {
            if (this == &other)
                return *this;

            title = other.title;
            width = other.width;
            height = other.height;
            isFullScreened = other.isFullScreened;;

            return *this;
        }
    };
}