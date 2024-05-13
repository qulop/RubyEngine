if(POLICY CMP0079)
    cmake_policy(SET CMP0079 NEW)
endif()

if(POLICY CMP0076)
    cmake_policy(SET CMP0076 NEW)
endif()

set(ROOT_DIR ${CMAKE_SOURCE_DIR})

function(GO_TO_ROOT_DIR)
    set(CURRENT_PATH ${ROOT_DIR})

    foreach (i RANGE 4)
        cmake_path(GET CURRENT_PATH PARENT_PATH PARENT_DIR)
        set(CURRENT_PATH ${PARENT_DIR})

        if (EXISTS ${CURRENT_PATH}/extern)
            set(ROOT_DIR ${CURRENT_PATH} PARENT_SCOPE)
            return()
        endif()

        message(FATAL_ERROR "[FATAL ERROR] Failed to find extern directory.")
    endforeach ()
endfunction()


if (NOT EXISTS ${ROOT_DIR}/extern)
    GO_TO_ROOT_DIR()
endif()

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC include/
                           ${CMAKE_PROJECT_NAME} PRIVATE ${ROOT_DIR}/extern/json/single_include/
                           ${CMAKE_PROJECT_NAME} PRIVATE ${ROOT_DIR}/extern/glfw/include/
                           ${CMAKE_PROJECT_NAME} PRIVATE ${ROOT_DIR}/extern/glad/include/
                           ${CMAKE_PROJECT_NAME} PRIVATE ${ROOT_DIR}/extern/spdlog/include/
                           ${CMAKE_PROJECT_NAME} PRIVATE ${ROOT_DIR}/extern/freetype2/include/
                           ${CMAKE_PROJECT_NAME} PRIVATE ${ROOT_DIR}/extern/glm/
                           ${CMAKE_PROJECT_NAME} PRIVATE ${ROOT_DIR}/extern/stb/)