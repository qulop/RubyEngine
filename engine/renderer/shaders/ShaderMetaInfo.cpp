#include "ShaderMetaInfo.hpp"

#include <utility/Assert.hpp>


namespace Kiwi {
    bool ShaderMetaInfo::IsFloatShaderType(EShaderDataTypes type) {
        switch (type) {
            case EShaderDataTypes::FLOAT:
            case EShaderDataTypes::VEC2:
            case EShaderDataTypes::VEC3:
            case EShaderDataTypes::VEC4:
                return true;

            default:
                return false;
        }
    }

    bool ShaderMetaInfo::IsIntShaderType(EShaderDataTypes type) {
        switch (type) {
            case EShaderDataTypes::INT:
            case EShaderDataTypes::IVEC2:
            case EShaderDataTypes::IVEC3:
            case EShaderDataTypes::IVEC4:
            case EShaderDataTypes::BOOL:
                return true;

            default:
                return false;
        }
    }

    bool ShaderMetaInfo::IsMatrixShaderType(EShaderDataTypes type) {
        return (type == EShaderDataTypes::MAT3) || (type == EShaderDataTypes::MAT4);
    }


    i32 ShaderMetaInfo::GetEShaderDataTypesize(EShaderDataTypes type) {
        switch (type) {
            case EShaderDataTypes::FLOAT:
            case EShaderDataTypes::INT: return 4;

            case EShaderDataTypes::VEC2:
            case EShaderDataTypes::IVEC2: return 4 * 2;

            case EShaderDataTypes::VEC3:
            case EShaderDataTypes::IVEC3: return 4 * 3;

            case EShaderDataTypes::VEC4:
            case EShaderDataTypes::IVEC4: return 4 * 4;

            case EShaderDataTypes::BOOL: return 4;

            case EShaderDataTypes::MAT3: return 4 * 3 * 3;
            case EShaderDataTypes::MAT4: return 4 * 4 * 4;

            default:
                std::unreachable();
        }
    }

    i32 ShaderMetaInfo::GetElementsCountInShaderDataType(EShaderDataTypes type, bool getCountInRow) {
        switch (type) {
            case EShaderDataTypes::INT:
            case EShaderDataTypes::FLOAT:
            case EShaderDataTypes::BOOL:
                return 1;

            case EShaderDataTypes::VEC2:
            case EShaderDataTypes::IVEC2:
                return 2;

            case EShaderDataTypes::VEC3:
            case EShaderDataTypes::IVEC3:
                return 3;

            case EShaderDataTypes::VEC4:
            case EShaderDataTypes::IVEC4:
                return 4;

            case EShaderDataTypes::MAT3: 
                return (getCountInRow) ? 3 : (3 * 3);
            case EShaderDataTypes::MAT4: 
                return (getCountInRow) ? 4 : (4 * 4);

            default:
                std::unreachable();
        }
    }
}