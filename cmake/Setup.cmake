function(trg_target_include_directories TARGET_NAME)
    target_include_directories(
        ${TARGET_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/engine/
        ${TARGET_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/third_party/json/single_include/
        ${TARGET_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/third_party/glfw/include/
        ${TARGET_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/third_party/spdlog/include/
        ${TARGET_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/third_party/freetype2/include/
        ${TARGET_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/third_party/glm/
        ${TARGET_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/third_party/stb/
        ${TARGET_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/third_party/ImGui 
    )

    # Graphic API includes
    target_include_directories(
        ${TARGET_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/third_party/glad/include/    # OpenGL
    )
endfunction()


function(trg_postsetup TARGET_NAME)
    set_target_properties(${TARGET_NAME} 
        PROPERTIES LINKER_LANGUAGE CXX
    )
endfunction()


function(trg_setup_library TARGET_NAME)
    message(STATUS "[STATUS]: Setting up a static library: ${TARGET_NAME}...")

	add_library(${TARGET_NAME} STATIC ${ENGINE_LIBRARY_SRC})

	find_package(OpenGL REQUIRED)
    target_link_libraries(${TARGET_NAME} 
        PRIVATE glfw
        PRIVATE glad
        PRIVATE freetype
        PRIVATE ImGui
        PRIVATE ${OpenGL_LIBRARIES}
    )
    if(WIN32)
        target_link_libraries(${TARGET_NAME} PRIVATE Winmm)
    endif()

    trg_target_include_directories(${TARGET_NAME})
    trg_postsetup(${TARGET_NAME})
endfunction()


function(trg_setup_application TARGET_NAME LIBRARY_NAME) 
    message(STATUS "[STATUS]: Setting up a main application...")

    add_executable(${TARGET_NAME} ${ENGINE_APPLICATION_SRC})
    target_link_libraries(${TARGET_NAME} PUBLIC 
        ${LIBRARY_NAME}
    )
    
    trg_target_include_directories(${TARGET_NAME})
    trg_postsetup(${TARGET_NAME})

    add_custom_command(
        TARGET ${ENGINE_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_CURRENT_SOURCE_DIR}/resources
                $<TARGET_FILE_DIR:${ENGINE_NAME}>/resources
        COMMENT "[POST-BUILD INFO]: Moving resources folder to the target directory..."
    )
endfunction()