#pragma once

#include "EnumReflector.hpp"


#define RUBY_ENUM(enumName, ...)  \
        RUBY_CREATE_ENUM(enumName, namespace, i32, __VA_ARGS__)

#define RUBY_ENUM_INNER(enumName, ...) \
        RUBY_CREATE_ENUM(enumName, class, i32, __VA_ARGS__)
