cmake_minimum_required(VERSION 3.5)
project(RubyDemo)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)

add_compile_definitions(RUBY_WIN32_USED)
cmake_path(GET PROJECT_SOURCE_DIR PARENT_PATH PARENT)

add_executable(${CMAKE_PROJECT_NAME} cxx/Main.cxx)

add_subdirectory(${PARENT}/ruby ${CMAKE_CURRENT_BINARY_DIR}/include_dirs)
target_link_libraries(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/RubyEngine.lib)