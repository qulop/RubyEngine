#include "ShaderMetaInfo.hpp"

#include <types/Logger.hpp>
#include <utility/Assert.hpp>


namespace Ruby {
    bool ShaderMetaInfo::IsFloatShaderType(ShaderDataTypes type) {
        switch (type) {
            case ShaderDataTypes::FLOAT:
            case ShaderDataTypes::VEC2:
            case ShaderDataTypes::VEC3:
            case ShaderDataTypes::VEC4:
                return true;

            default:
                return false;
        }
    }

    bool ShaderMetaInfo::IsIntShaderType(ShaderDataTypes type) {
        switch (type) {
            case ShaderDataTypes::INT:
            case ShaderDataTypes::IVEC2:
            case ShaderDataTypes::IVEC3:
            case ShaderDataTypes::IVEC4:
            case ShaderDataTypes::BOOL:
                return true;

            default:
                return false;
        }
    }

    bool ShaderMetaInfo::IsMatrixShaderType(ShaderDataTypes type) {
        return (type == ShaderDataTypes::MAT3) || (type == ShaderDataTypes::MAT4);
    }


    i32 ShaderMetaInfo::GetShaderDataTypeSize(ShaderDataTypes type) {
        switch (type) {
            case ShaderDataTypes::FLOAT:
            case ShaderDataTypes::INT: return 4;

            case ShaderDataTypes::VEC2:
            case ShaderDataTypes::IVEC2: return 4 * 2;

            case ShaderDataTypes::VEC3:
            case ShaderDataTypes::IVEC3: return 4 * 3;

            case ShaderDataTypes::VEC4:
            case ShaderDataTypes::IVEC4: return 4 * 4;

            case ShaderDataTypes::BOOL: return 4;

            case ShaderDataTypes::MAT3: return 4 * 3 * 3;
            case ShaderDataTypes::MAT4: return 4 * 4 * 4;

            default:
                RUBY_CRITICAL("getShaderDataTypeSize() : Unknown shader type!");
                return 0;
        }
    }

    i32 ShaderMetaInfo::GetElementsCountInShaderDataType(ShaderDataTypes type, bool getCountInRow) {
        switch (type) {
            case ShaderDataTypes::INT:
            case ShaderDataTypes::FLOAT:
            case ShaderDataTypes::BOOL:
                return 1;

            case ShaderDataTypes::VEC2:
            case ShaderDataTypes::IVEC2:
                return 2;

            case ShaderDataTypes::VEC3:
            case ShaderDataTypes::IVEC3:
                return 3;

            case ShaderDataTypes::VEC4:
            case ShaderDataTypes::IVEC4:
                return 4;

            case ShaderDataTypes::MAT3: 
                return (getCountInRow) ? 3 : (3 * 3);
            case ShaderDataTypes::MAT4: 
                return (getCountInRow) ? 4 : (4 * 4);

            default:
                RUBY_CRITICAL("getShaderTypeElementsCount() : Unknown shader type!");
                return 0;
        }
    }
}