#include <render/ShaderTypes.hpp>
#include <utility/Logger.hpp>


namespace Ruby
{
    bool isFloatShaderType(ShaderTypes type) {
        switch (type) {
            case ShaderTypes::FLOAT:
            case ShaderTypes::VEC2:
            case ShaderTypes::VEC3:
            case ShaderTypes::VEC4:
                return true;

            default:
                return false;
        }
    }

    bool isIntShaderType(ShaderTypes type) {
        switch (type) {
            case ShaderTypes::INT:
            case ShaderTypes::IVEC2:
            case ShaderTypes::IVEC3:
            case ShaderTypes::IVEC4:
            case ShaderTypes::BOOL:
                return true;

            default:
                return false;
        }
    }

    bool isMatrixShaderType(ShaderTypes type)
    { return (type == ShaderTypes::MAT3) || (type == ShaderTypes::MAT4); }

    i32 getShaderTypeSize(ShaderTypes type)
    {
        switch(type)
        {
            case ShaderTypes::FLOAT:
            case ShaderTypes::INT: return 4;

            case ShaderTypes::VEC2:
            case ShaderTypes::IVEC2: return 4 * 2;

            case ShaderTypes::VEC3:
            case ShaderTypes::IVEC3: return 4 * 3;

            case ShaderTypes::VEC4:
            case ShaderTypes::IVEC4: return 4 * 4;

            case ShaderTypes::BOOL: return 1;

            case ShaderTypes::MAT3: return 4 * 3 * 3;
            case ShaderTypes::MAT4: return 4 * 4 * 4;

            default:
                RUBY_ERROR("getShaderTypeSize() : Unknown shader type!");
        }
    }

    i32 getShaderTypeElementsCount(ShaderTypes type, bool getActualSize)
    {
        switch(type)
        {
            case ShaderTypes::INT:
            case ShaderTypes::FLOAT:
            case ShaderTypes::BOOL:
                return 1;

            case ShaderTypes::VEC2:
            case ShaderTypes::IVEC2:
                return 2;

            case ShaderTypes::VEC3:
            case ShaderTypes::IVEC3:
                return 3;

            case ShaderTypes::VEC4:
            case ShaderTypes::IVEC4:
                return 4;

            case ShaderTypes::MAT3: return (getActualSize) ? 3 * 3 : 3;
            case ShaderTypes::MAT4: return (getActualSize) ? 4 * 4 : 4;

            default:
                RUBY_ERROR("getShaderTypeElementsCount() : Unknown shader type!");
        }
    }
}