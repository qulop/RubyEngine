#pragma once

#include <platform/linux/Linux.hpp>

#include <X11/Xlib.h>


namespace Ruby::Linux
{
    std::pair<i32, i32> getScreenResolution() noexcept
    {
        Display* display = XOpenDisplay(NULL);
        Screen* screen = DefaultScreenOfDisplay(display);

        auto res = std::make_pair(WidthOfScreen(screen), HeightOfScreen(screen));
        XCloseDisplay(display);

        return res;
    }
}