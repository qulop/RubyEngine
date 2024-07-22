#pragma once

#include <utility/Definitions.hpp>


namespace Ruby {
    enum class ShaderDataTypes {
        NONE,
        INT, IVEC2, IVEC3, IVEC4,
        BOOL,
        FLOAT, VEC2, VEC3, VEC4,
        MAT3, MAT4
    };

    bool isFloatShaderType(ShaderDataTypes type);
    bool isIntShaderType(ShaderDataTypes type);
    bool isMatrixShaderType(ShaderDataTypes type);

    i32 getShaderDataTypeSize(ShaderDataTypes type);
    i32 getShaderTypeElementsCount(ShaderDataTypes type, bool getActualSize = true);
}