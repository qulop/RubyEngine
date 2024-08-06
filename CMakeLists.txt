if(NOT WIN32)
    message(FATAL_ERROR "Ruby was designed only for Windows!")
endif()

cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project("RubyEngine" LANGUAGES CXX)

option(RUBY_UNIT_TESTS "" OFF)
message(STATUS "[BUILD INFO]: Build in unit-tests mode: ${RUBY_UNIT_TESTS}")


# CMake policy section
if(POLICY CMP0077)
	cmake_policy(SET CMP0077 NEW)
endif()
# -----------------------

# CMake config
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)
# -----------------------

if(WIN32)
    add_compile_definitions(RUBY_WIN32_USED)
elseif(UNIX)
    add_compile_definitions(RUBY_LINUX_USED)
endif()

# compilers flags
if (MSVC)
    add_compile_options(/wd4251)
    add_compile_definitions(RUBY_MSVC_USED)
elseif(GNUC)
    add_compile_options(-Wno-attributes)
    add_compile_definitions(RUBY_GCC_USED)
elseif(CLANG)
    add_compile_options(-Wno-undefined-var-template)
    add_compile_definitions(RUBY_CLANG_USED)
endif()
#----------------------

# variables for GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
# -----------------------


add_compile_definitions(RUBY_ENGINE_BUILD RUBY_OPENGL_USED)
if (CMAKE_BUILD_TYPE EQUAL Release)
	add_compile_definitions(_NDEBUG RUBY_RELEASE_BUILD)
else()
    add_compile_definitions(RUBY_DEBUG_BUILD)
endif()

set(IMGUI_GLFW_PATH   ${CMAKE_CURRENT_SOURCE_DIR}/extern/glfw)
set(IMGUI_OPENGL3_GLFW ON CACHE BOOL "" FORCE)

message(STATUS "[BUILD INFO]: Subdirectories configuration...")
add_subdirectory(extern/glad)
add_subdirectory(extern/freetype2)
add_subdirectory(extern/ImGui)

set(RUBY_SRC    cxx/Core.cxx
                cxx/Graphics.cxx
                cxx/Utility.cxx
                cxx/Platform.cxx
                cxx/Renderer.cxx
)

if (RUBY_UNIT_TESTS)
    list(APPEND RUBY_SRC cxx/Tests.cxx)

    add_executable(${PROJECT_NAME} ${RUBY_SRC})
else()
    add_library(${PROJECT_NAME} SHARED ${RUBY_SRC})
endif()


message(STATUS "[BUILD INFO]: Collected sources:")
foreach(src IN LISTS RUBY_SRC)
    message(STATUS "   [FILE]: ${src}")
endforeach()


target_link_libraries(${PROJECT_NAME} PRIVATE glfw
                                      PRIVATE glad
                                      PRIVATE freetype
                                      PRIVATE opengl32
                                      PRIVATE ImGui)

set_target_properties(${PROJECT_NAME} 
                        PROPERTIES 
                            LINKER_LANGUAGE CXX)

add_subdirectory("ruby/")

add_custom_command(
        TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_CURRENT_SOURCE_DIR}/resources
                $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>/resources
        COMMENT "[POST-BUILD INFO]: Moving resources folder to the target directory..."
)