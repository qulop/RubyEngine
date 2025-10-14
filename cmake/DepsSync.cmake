function(trg_shaderc_sync_deps)
    find_package(Python COMPONENTS Interpreter REQUIRED)
    
    message(STATUS "[INFO]: Trying to sync shaderc dependencies...")
    execute_process(
        COMMAND ${Python_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/third_party/shaderc/utils/git-sync-deps
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/third_party/shaderc
        RESULT_VARIABLE result
    )

    if (NOT result EQUAL 0)
        message(FATAL_ERROR "[ERROR]: Failed to sync shaderc dependencies!")
    endif()
endfunction()