function(kiwi_target_include_directories TARGET_NAME)
    target_include_directories(
        ${TARGET_NAME} PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/engine/
        ${TARGET_NAME} PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/editor/
        ${TARGET_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/third_party/json/single_include/
        ${TARGET_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/third_party/glfw/include/
        ${TARGET_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/third_party/spdlog/include/
        ${TARGET_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/third_party/freetype2/include/
        ${TARGET_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/third_party/glm/
        ${TARGET_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/third_party/stb/
        ${TARGET_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/third_party/ImGui 
        ${TARGET_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/third_party/shaderc/libshaderc/include
        ${TARGET_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/third_party/xxHash
        ${TARGET_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/third_party/tracy/public
        ${TARGET_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/third_party/vma/include
    )

    if (${TARGET_NAME} EQUAL ${ENGINE_EDITOR_NAME})
        target_include_directories(${TARGET_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/editor/)
    endif()
endfunction()


function(kiwi_post_setup TARGET_NAME)
    set_target_properties(${TARGET_NAME} 
        PROPERTIES LINKER_LANGUAGE CXX
    )
endfunction()


function(kiwi_setup_library TARGET_NAME)
    message(STATUS "[STATUS]: Setting up a static library: ${TARGET_NAME}...")

	add_library(${TARGET_NAME} STATIC ${ENGINE_LIBRARY_SRC})

	find_package(OpenGL REQUIRED)
    target_link_libraries(${TARGET_NAME} 
        PRIVATE glfw
        PRIVATE freetype
        PRIVATE ImGui
        PRIVATE shaderc
        PRIVATE xxhash
        PRIVATE Tracy::TracyClient
    )
    if(WIN32)
        target_link_libraries(${TARGET_NAME} PRIVATE Winmm)
    endif()

    kiwi_target_include_directories(${TARGET_NAME})

    # Graphic API setting
    kiwi_update_target_with_VULKAN(${TARGET_NAME})
    kiwi_update_target_with_OPENGL(${TARGET_NAME})

    kiwi_post_setup(${TARGET_NAME})
endfunction()


function(kiwi_setup_application TARGET_NAME LIBRARY_NAME) 
    message(STATUS "[STATUS]: Setting up the main application...")

    add_executable(${TARGET_NAME} ${ENGINE_APPLICATION_SRC})
    target_link_libraries(${TARGET_NAME} PUBLIC 
        ${LIBRARY_NAME}
    )

    if (WIN32)
        set_target_properties(${TARGET_NAME} PROPERTIES 
            WIN32_EXECUTABLE TRUE
        )
    endif()
    
    kiwi_target_include_directories(${TARGET_NAME})
    kiwi_post_setup(${TARGET_NAME})

    add_custom_command(
        TARGET ${TARGET_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_CURRENT_SOURCE_DIR}/resources
                $<TARGET_FILE_DIR:${TARGET_NAME}>/resources
        COMMENT "[POST-BUILD INFO]: Moving resources folder to the target directory..."
    )
endfunction()