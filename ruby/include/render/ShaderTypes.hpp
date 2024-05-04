#pragma once

#include <utility/Definitions.hpp>


namespace Ruby
{
    enum class ShaderTypes
    {
        NONE,
        INT, IVEC2, IVEC3, IVEC4,
        BOOL,
        FLOAT, VEC2, VEC3, VEC4,
        MAT3, MAT4
    };

    bool isFloatShaderType(ShaderTypes type);
    bool isIntShaderType(ShaderTypes type);
    bool isMatrixShaderType(ShaderTypes type);

    i32 getShaderTypeSize(ShaderTypes type);
    i32 getShaderTypeElementsCount(ShaderTypes type, bool getActualSize = true);
}