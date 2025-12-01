set(KIWI_VULKAN_SDK_PATH "$ENV{VULKAN_SDK}/Include")
set(KIWI_VULKAN_LIB_PATH "$ENV{VULKAN_SDK}/Lib")


function(kiwi_update_target_with_VULKAN TARGET_NAME)
    find_package(Vulkan REQUIRED)

    target_include_directories(
            ${TARGET_NAME} PUBLIC ${KIWI_VULKAN_SDK_PATH}
    )

    target_link_libraries(${TARGET_NAME} PUBLIC ${Vulkan_LIBRARIES})

    message(STATUS "[INFO]: Vulkan setting done")
endfunction()


