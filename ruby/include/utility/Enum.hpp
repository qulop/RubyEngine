#pragma once

#include "EnumReflector.hpp"


#define RUBY_ENUM(enumName, type, ...)  \
        RUBY_CREATE_ENUM(enumName, type, ...)