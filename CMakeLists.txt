if(NOT WIN32)
    message(FATAL_ERROR "Kiwi Engine only supports Windows at this moment")
endif()

cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project("KiwiEngine" LANGUAGES CXX)


option(KIWI_BUILD_ONLY_LIBRARY "Allows to build only the engine library without compiling the editor code" OFF)
option(KIWI_ENABLE_PROFILING "" ON)


include(cmake/CmakePolicy.cmake)
kiwi_setup_required_cmake_policies()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_C_STANDARD 11)

set(ENGINE_EDITOR_NAME ${CMAKE_PROJECT_NAME})
set(ENGINE_LIBRARY_NAME "KiwiLib")


if(WIN32)
    add_compile_definitions(KIWI_WIN32_USED)
elseif(UNIX)
    add_compile_definitions(KIWI_LINUX_USED)
endif()

include(TestBigEndian)
test_big_endian(PLATFORM_IS_BIG_ENDIAN)

if (PLATFORM_IS_BIG_ENDIAN)
    add_compile_definitions(KIWI_BIG_ENDIAN)
else()
    add_compile_definitions(KIWI_LITTLE_ENDIAN)
endif()


if (MSVC)
    add_compile_definitions(KIWI_MSVC_USED)
    add_compile_options(
            /wd4251
            /Zc:preprocessor
            /Zc:__cplusplus
            /permissive-
            /Zc:referenceBinding
            /Zc:strictStrings
    )
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_compile_definitions(KIWI_GCC_USED)
    add_compile_options(
            -Wno-attributes
            -masm=intel
    )
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_compile_definitions(KIWI_CLANG_USED)
    add_compile_options(
            -Wno-undefined-var-template
            -masm=intel
    )
endif()


if (CMAKE_BUILD_TYPE EQUAL Release)
	add_compile_definitions(KIWI_RELEASE_BUILD)
else()
    add_compile_definitions(KIWI_DEBUG_BUILD)
endif()

if (KIWI_ENABLE_PROFILING)
    add_compile_definitions(TRACY_ENABLE KIWI_ENABLE_PROFILING)
endif()


set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

set(IMGUI_GLFW_PATH   ${CMAKE_CURRENT_SOURCE_DIR}/third_party/glfw)
set(IMGUI_OPENGL3_GLFW ON CACHE BOOL "" FORCE)

set(SHADERC_SKIP_TESTS ON CACHE BOOL "" FORCE)
set(SHADERC_SKIP_EXAMPLES ON CACHE BOOL "" FORCE)
set(SHADERC_SKIP_EXECUTABLES ON CACHE BOOL "" FORCE)
set(SHADERC_SKIP_COPYRIGHT_CHECK ON CACHE BOOL "" FORCE)
set(SHADERC_SKIP_INSTALL OFF CACHE BOOL "" FORCE)

set(XXHASH_BUILD_XXHSUM OFF CACHE BOOL "" FORCE)
set(XXHASH_BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

set(TRACY_ENABLE ON CACHE BOOL "" FORCE)
set(TRACY_ON_DEMAND ON CACHE BOOL "" FORCE)
set(TRACY_STATIC ON CACHE BOOL "" FORCE)
set(TRACY_NO_EXIT ON CACHE BOOL "" FORCE)


include(cmake/DepsSync.cmake)
kiwi_shaderc_sync_deps()


message(STATUS "[INFO]: Subdirectories configuration...")
add_subdirectory(third_party/glad)
add_subdirectory(third_party/freetype2)
add_subdirectory(third_party/ImGui)
add_subdirectory(third_party/shaderc)
add_subdirectory(third_party/xxHash)
add_subdirectory(third_party/tracy)

include(cmake/EngineSources.cmake)
include(cmake/Setup.cmake)

kiwi_setup_library(${ENGINE_LIBRARY_NAME})
if (NOT ${KIWI_BUILD_ONLY_LIBRARY})
    kiwi_setup_application(${ENGINE_EDITOR_NAME} ${ENGINE_LIBRARY_NAME})
else()
    message(STATUS "[INFO]: Skipping the application setup, because KIWI_BUILD_ONLY_LIBRARY=ON")
endif()
