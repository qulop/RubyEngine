if(NOT WIN32)
    message(FATAL_ERROR "TrgEngine only supports Windows at this moment")
endif()

cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project("TrgEngine" LANGUAGES CXX)


include(cmake/CmakePolicy.cmake)
trg_setup_required_cmake_policies()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_C_STANDARD 11)

set(ENGINE_NAME ${CMAKE_PROJECT_NAME})
set(ENGINE_LIBRARY_NAME "TrgLib")


if(WIN32)
    add_compile_definitions(RUBY_WIN32_USED)
elseif(UNIX)
    add_compile_definitions(RUBY_LINUX_USED)
endif()


if (MSVC)
    add_compile_definitions(RUBY_MSVC_USED)
    add_compile_options(/wd4251 /Zc:preprocessor /Zc:__cplusplus)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_compile_definitions(RUBY_GCC_USED)
    add_compile_options(-Wno-attributes -masm=intel)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_compile_definitions(RUBY_CLANG_USED)
    add_compile_options(-Wno-undefined-var-template -masm=intel)
endif()


set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)


if (CMAKE_BUILD_TYPE EQUAL Release)
	add_compile_definitions(RUBY_RELEASE_BUILD)
else()
    add_compile_definitions(RUBY_DEBUG_BUILD)
endif()


set(IMGUI_GLFW_PATH   ${CMAKE_CURRENT_SOURCE_DIR}/third_party/glfw)
set(IMGUI_OPENGL3_GLFW ON CACHE BOOL "" FORCE)


message(STATUS "[BUILD INFO]: Subdirectories configuration...")
add_subdirectory(third_party/glad)
add_subdirectory(third_party/freetype2)
add_subdirectory(third_party/ImGui)

include(cmake/EngineSources.cmake)
include(cmake/Setup.cmake)

trg_setup_library(${ENGINE_LIBRARY_NAME})
trg_setup_application(${ENGINE_NAME} ${ENGINE_LIBRARY_NAME})
