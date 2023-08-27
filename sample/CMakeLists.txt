cmake_minimum_required(VERSION 3.4)
project(sample)



include_directories(${PROJECT_SOURCE_DIR}/../src/)

add_executable(${PROJECT_NAME} "game/main.cpp")
target_link_libraries(${PROJECT_NAME} libRubyVn.dll.a)