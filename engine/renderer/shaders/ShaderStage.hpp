#pragma once

#include <types/Logger.hpp>
#include <types/cast/Cast.hpp>

#include <shaderc/shaderc.hpp>
#include <glad/glad.h>


namespace Kiwi {
    enum class EShaderStage : u8 {
        NONE,

        VERTEX,
        TESS_CONTROL, TESS_EVALUATION,
        GEOMETRY,
        FRAGMENT,
        COMPUTE,

        SHADER_PROGRAM
    };


    template<>
    struct CastTraits<EShaderStage> {
        KIWI_NODISCARD KIWI_FORCEINLINE static Opt<shaderc_shader_kind> ToShaderCKind(EShaderStage stage) {
            switch (stage) {
                case EShaderStage::VERTEX:
                    return shaderc_vertex_shader;
                case EShaderStage::TESS_CONTROL:
                    return shaderc_tess_control_shader;
                case EShaderStage::TESS_EVALUATION:
                    return shaderc_tess_evaluation_shader;
                case EShaderStage::GEOMETRY:
                    return shaderc_geometry_shader;
                case EShaderStage::FRAGMENT:
                    return shaderc_fragment_shader;
                case EShaderStage::COMPUTE:
                    return shaderc_compute_shader;
                default:
                    KIWI_ERROR("CastTraits<EShaderStage>::ToShaderCKind() : Unknown stage received.");
                    return nullopt;
            }
        }
    
        KIWI_NODISCARD KIWI_FORCEINLINE static Opt<GLenum> ToGLenum(EShaderStage stage) {
            switch (stage) {
                case EShaderStage::VERTEX:
                    return GL_VERTEX_SHADER;
                case EShaderStage::TESS_CONTROL:
                    return GL_TESS_CONTROL_SHADER;
                case EShaderStage::TESS_EVALUATION:
                    return GL_TESS_EVALUATION_SHADER;
                case EShaderStage::GEOMETRY:
                    return GL_GEOMETRY_SHADER;
                case EShaderStage::FRAGMENT:
                    return GL_FRAGMENT_SHADER;
                case EShaderStage::COMPUTE:
                    return GL_COMPUTE_SHADER;
                default:
                    KIWI_ERROR("shaderStageToGLenum() : Unknown stage received");
                    return nullopt;
            }
        }
    };
}