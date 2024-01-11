#pragma once

#if defined(_WIN32) || defined(WIN32) || defined(__WIN32__) || defined(__NT__) || defined(_WIN64)

#pragma warning(push)
#pragma warning(disable : 4996)

    #include "core/RubyApp.hpp"
    #include "core/Window.hpp"
    #include "core/WindowProps.hpp"
    #include "event/Event.hpp"

#pragma warning(pop)

#endif