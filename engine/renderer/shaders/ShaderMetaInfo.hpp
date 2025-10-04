#pragma once

#include <utility/Definitions.hpp>


namespace Ruby {
    enum class EShaderDataTypes {
        NONE,
        INT, IVEC2, IVEC3, IVEC4,
        BOOL,
        FLOAT, VEC2, VEC3, VEC4,
        MAT3, MAT4
    };


    class ShaderMetaInfo {
    public:
        RUBY_NODISCARD static bool IsFloatShaderType(EShaderDataTypes type);
        RUBY_NODISCARD static bool IsIntShaderType(EShaderDataTypes type);
        RUBY_NODISCARD static bool IsMatrixShaderType(EShaderDataTypes type);

        RUBY_NODISCARD static i32 GetEShaderDataTypesize(EShaderDataTypes type);
        RUBY_NODISCARD static i32 GetElementsCountInShaderDataType(EShaderDataTypes type, bool getCountInRow = false);
    };
}