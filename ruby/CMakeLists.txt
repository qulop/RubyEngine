if(POLICY CMP0079)
    cmake_policy(SET CMP0079 NEW)
endif()

if(POLICY CMP0076)
    cmake_policy(SET CMP0076 NEW)
endif()

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC include/
                           ${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/extern/json/single_include
                           ${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/extern/glfw/include
                           ${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/extern/glad/include
                           ${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/extern/spdlog/include
                           ${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/extern/freetype2/include
                           ${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/extern/glm
                           ${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/extern/stb)