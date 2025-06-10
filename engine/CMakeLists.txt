if(POLICY CMP0079)
    cmake_policy(SET CMP0079 NEW)
endif()

if(POLICY CMP0076)
    cmake_policy(SET CMP0076 NEW)
endif()

function(trg_try_to_find_root_directory)
    set(CURRENT_PATH ${CMAKE_SOURCE_DIR})

    foreach (i RANGE 4)
        cmake_path(GET CURRENT_PATH PARENT_PATH PARENT_DIR)
        set(CURRENT_PATH ${PARENT_DIR})

        if (EXISTS ${CURRENT_PATH}/extern)
            set(${CMAKE_SOURCE_DIR} ${CURRENT_PATH} PARENT_SCOPE)
            return()
        endif()

        message(FATAL_ERROR "[FATAL ERROR] Failed to find extern directory.")
    endforeach ()
endfunction()


function(trg_target_include_directories TARGET_NAME)
    if (NOT EXISTS ${CMAKE_SOURCE_DIR}/extern)
        trg_try_to_find_root_directory()
    endif()

    target_include_directories(
        ${TARGET_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/
        ${TARGET_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/tests/
        ${TARGET_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/extern/json/single_include/
        ${TARGET_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/extern/glfw/include/
        ${TARGET_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/extern/glad/include/
        ${TARGET_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/extern/spdlog/include/
        ${TARGET_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/extern/freetype2/include/
        ${TARGET_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/extern/glm/
        ${TARGET_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/extern/stb/
        ${TARGET_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/extern/ImGui 
    )
endfunction()

trg_target_include_directories(${ENGINE_LIBRARY_NAME})
trg_target_include_directories(${ENGINE_NAME})
