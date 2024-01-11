cmake_minimum_required(VERSION 3.4)
project(RubyDemo)

if(POLICY CMP0079)
    cmake_policy(SET CMP0079 NEW)
endif()

if(POLICY CMP0076)
    cmake_policy(SET CMP0076 NEW)
endif()


cmake_path(GET PROJECT_SOURCE_DIR PARENT_PATH PARENT)

add_subdirectory(${PARENT}/ruby ${CMAKE_CURRENT_BINARY_DIR}/demo)


set(DEMO ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(${PROJECT_NAME} PUBLIC "src/Main.cpp")
target_link_libraries(${PROJECT_NAME} ${DEMO}/RubyEngine.lib)