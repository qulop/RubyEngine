set(KIWI_OPENGL_SDK_PATH ${CMAKE_CURRENT_SOURCE_DIR}/third_party/glad/include/)


function(kiwi_update_target_with_OPENGL TARGET_NAME)
    find_package(OpenGL REQUIRED)

    target_include_directories(
            ${TARGET_NAME} PUBLIC ${KIWI_OPENGL_SDK_PATH}
    )

    target_link_libraries(${TARGET_NAME}
            PUBLIC ${OpenGL_LIBRARIES}
            PUBLIC glad
    )

    message(STATUS "[INFO]: OpenGL setting done")
endfunction()
