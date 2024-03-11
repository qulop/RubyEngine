if(NOT WIN32)
    message(FATAL_ERROR "Ruby was designed only for Windows!")
endif()


if(POLICY CMP0079)
    cmake_policy(SET CMP0079 NEW)
endif()

if(POLICY CMP0076)
    cmake_policy(SET CMP0076 NEW)
endif()

cmake_path(GET CMAKE_CURRENT_SOURCE_DIR PARENT_PATH PARENT)

target_include_directories(${PROJECT_NAME} PUBLIC include/)
target_include_directories(${PROJECT_NAME} PRIVATE ${PARENT}/extern/json/single_include)
target_include_directories(${PROJECT_NAME} PRIVATE ${PARENT}/extern/glfw/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${PARENT}/extern/glad/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${PARENT}/extern/spdlog/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${PARENT}/extern/freetype2/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${PARENT}/extern/glm)
target_include_directories(${PROJECT_NAME} PRIVATE ${PARENT}/extern/soil/include)