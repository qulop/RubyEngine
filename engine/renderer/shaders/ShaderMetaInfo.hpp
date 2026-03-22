#pragma once

#include <common/Definitions.hpp>


namespace Kiwi {
    enum class EShaderDataTypes {
        NONE,
        INT, IVEC2, IVEC3, IVEC4,
        BOOL,
        FLOAT, VEC2, VEC3, VEC4,
        MAT3, MAT4
    };


    class ShaderMetaInfo {
    public:
        KIWI_NODISCARD static bool IsFloatShaderType(EShaderDataTypes type);
        KIWI_NODISCARD static bool IsIntShaderType(EShaderDataTypes type);
        KIWI_NODISCARD static bool IsMatrixShaderType(EShaderDataTypes type);

        KIWI_NODISCARD static i32 GetShaderDataTypeSize(EShaderDataTypes type);
        KIWI_NODISCARD static i32 GetElementsCountInShaderDataType(EShaderDataTypes type, bool getCountInRow = false);
    };
}