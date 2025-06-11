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

        if (EXISTS ${CURRENT_PATH}/third_party)
            set(${CMAKE_SOURCE_DIR} ${CURRENT_PATH} PARENT_SCOPE)
            return()
        endif()

        message(FATAL_ERROR "[FATAL ERROR] Failed to find extern directory.")
    endforeach ()
endfunction()


function(trg_target_include_directories TARGET_NAME)
    if (NOT EXISTS ${CMAKE_SOURCE_DIR}/third_party)
        trg_try_to_find_root_directory()
    endif()

    target_include_directories(
        ${TARGET_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/
        ${TARGET_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/tests/
        ${TARGET_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/third_party/json/single_include/
        ${TARGET_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/third_party/glfw/include/
        ${TARGET_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/third_party/glad/include/
        ${TARGET_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/third_party/spdlog/include/
        ${TARGET_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/third_party/freetype2/include/
        ${TARGET_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/third_party/glm/
        ${TARGET_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/third_party/stb/
        ${TARGET_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/third_party/ImGui 
    )
endfunction()

trg_target_include_directories(${ENGINE_LIBRARY_NAME})
trg_target_include_directories(${ENGINE_NAME})
