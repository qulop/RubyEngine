cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project("Tests" LANGUAGES CXX)

set(TESTS_SRC
    common/Result.test.cpp
)

set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
add_subdirectory(${CMAKE_SOURCE_DIR}/third_party/gtest ${CMAKE_CURRENT_BINARY_DIR}/gtest)


add_executable("Tests" ${TESTS_SRC})
target_include_directories("Tests"
    PRIVATE ${CMAKE_SOURCE_DIR}/engine/
    PRIVATE ${CMAKE_SOURCE_DIR}/third_party/gtest/googletest/include
)

target_link_libraries("Tests" ${ENGINE_LIBRARY_NAME})


include(CTest)
add_test(NAME "Tests" COMMAND "Tests")

