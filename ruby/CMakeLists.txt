if(NOT WIN32)
    message(FATAL_ERROR "Ruby was designed only for Windows!")
endif()


# CMake config
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 11)
# -----------------------


if(LIB_BUILD)
    cmake_path(GET CMAKE_CURRENT_SOURCE_DIR PARENT_PATH PARENT)

    file(GLOB_RECURSE 
            RUBY_SRC 
                ${PROJECT_SOURCE_DIR} "*.cpp")

    add_subdirectory(${PARENT}/extern/glfw ${CMAKE_CURRENT_BINARY_DIR}/glfw)	# GLFW Subdir
    add_subdirectory(${PARENT}/extern/glad ${CMAKE_CURRENT_BINARY_DIR}/glad)	# Glad Subdir
    
    add_library(${PROJECT_NAME} SHARED ${RUBY_SRC})

    
    target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
    target_link_libraries(${PROJECT_NAME} PRIVATE glad)
    set_target_properties(${PROJECT_NAME} 
                            PROPERTIES 
                                LINKER_LANGUAGE CXX)
else()
    add_executable(${PROJECT_NAME})
endif()

target_include_directories(${PROJECT_NAME} PUBLIC src/)
target_include_directories(${PROJECT_NAME} PRIVATE ${PARENT}/extern/)
target_include_directories(${PROJECT_NAME} PRIVATE ${PARENT}/extern/glad/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${PARENT}/extern/spdlog/include)

