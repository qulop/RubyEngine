if(NOT WIN32)
    message(FATAL_ERROR "Ruby was designed only for Windows!")
endif()

cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project("RubyEngine")


# CMake policy section
if(POLICY CMP0077)
	cmake_policy(SET CMP0077 NEW)
endif()

if(POLICY CMP0079)
    cmake_policy(SET CMP0079 NEW)
endif()
# -----------------------


# CMake config
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)
# -----------------------

# compilers flags
if (MSVC)
	add_compile_options(/wd4251)
    add_compile_options(/wd4996)        # for spdlog(fmt) library
    add_compile_options(/std:c++latest)
elseif(GNUC)
	add_compile_options(-Wno-attributes)
    add_compile_options(-std=c++2b)
elseif(CLANG)
	add_compile_options(-Wno-undefined-var-template)
    add_compile_options(-std=c++2b)
endif()
#----------------------

# variables for GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
# -----------------------


add_compile_definitions(RUBY_BUILD RUBY_GLFW_BUILD)
if (CMAKE_BUILD_TYPE EQUAL Release)
	add_compile_definitions(_NDEBUG)
endif()


add_subdirectory(extern/glfw      ${CMAKE_CURRENT_BINARY_DIR}/glfw)
add_subdirectory(extern/glad      ${CMAKE_CURRENT_BINARY_DIR}/glad)
add_subdirectory(extern/freetype2 ${CMAKE_CURRENT_BINARY_DIR}/freetype)
add_subdirectory(extern/soil      ${CMAKE_CURRENT_BINARY_DIR}/soil)  


set(RUBY_SRC cxx/Core.cxx cxx/Render.cxx cxx/Utility.cxx cxx/Window.cxx)
add_library(${PROJECT_NAME} SHARED ${RUBY_SRC})


target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE glad)
target_link_libraries(${PROJECT_NAME} PRIVATE opengl32)
target_link_libraries(${PROJECT_NAME} PRIVATE freetype)
target_link_libraries(${PROJECT_NAME} PRIVATE soil)

set_target_properties(${PROJECT_NAME} 
                        PROPERTIES 
                            LINKER_LANGUAGE CXX)


add_subdirectory("ruby/")
