cmake_minimum_required(VERSION 3.4 FATAL_ERROR)
project("RubyVn")

# CMake policy section
if(POLICY CMP0077)
	cmake_policy(SET CMP0077 NEW)
endif()

if(POLICY CMP0079)
    cmake_policy(SET CMP0079 NEW)
endif()
# -----------------------

# variables for Ruby
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 11)
# -----------------------

# variables for GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
# -----------------------


add_compile_definitions(RUBY_BUILD)	# RUBY_BUILD - macro in Core.hpp for __declspec(dllexport)
if (CMAKE_BUILD_TYPE EQUAL Release)
	add_compile_definitions(_NDEBUG)
endif()

set(LIB_BUILD ON)	# For condition in ruby/CMakeLists.txt
add_subdirectory("ruby/")
