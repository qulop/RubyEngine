if(POLICY CMP0079)
    cmake_policy(SET CMP0079 NEW)
endif()

if(POLICY CMP0076)
    cmake_policy(SET CMP0076 NEW)
endif()

target_include_directories(${PROJECT_NAME} PUBLIC include/
                           ${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/extern/json/single_include
                           ${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/extern/glfw/include
                           ${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/extern/glad/include
                           ${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/extern/spdlog/include
                           ${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/extern/freetype2/include
                           ${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/extern/glm
                           ${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/extern/soil/include)