#pragma once

#include "EnumReflector.hpp"


#define KIWI_ENUM(enumName, ...)  \
        KIWI_CREATE_ENUM(enumName, namespace, i32, __VA_ARGS__)

#define KIWI_ENUM_INNER(enumName, ...) \
        KIWI_CREATE_ENUM(enumName, class, i32, __VA_ARGS__)
