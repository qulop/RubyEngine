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


    class ShaderMetaInfo {
    public:
        RUBY_NODISCARD static bool IsFloatShaderType(ShaderDataTypes type);
        RUBY_NODISCARD static bool IsIntShaderType(ShaderDataTypes type);
        RUBY_NODISCARD static bool IsMatrixShaderType(ShaderDataTypes type);

        RUBY_NODISCARD static i32 GetShaderDataTypeSize(ShaderDataTypes type);
        RUBY_NODISCARD static i32 GetElementsCountInShaderDataType(ShaderDataTypes type, bool getCountInRow = false);
    };
}