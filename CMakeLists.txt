cmake_minimum_required(VERSION 3.4)
project("RubyVn")

if(NOT WIN32)
	message(FATAL_ERROR "${PROJECT_NAME} was disigned only for Windows!")
endif()

include(GenerateExportHeader)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 11)
set(CMAKE_SHARED_LIBRARY_PREFIX "")	# FIX THIS
set(CMAKE_STATIC_LIBRARY_PREFIX "")	# FIX THIS
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

set(DLL_EXPORT_MACRO RUBY_BUILD)


add_compile_definitions(RUBY_WIN32 RUBY_BUILD)
if (CMAKE_BUILD_TYPE EQUAL Release)
	add_compile_definitions(_NDEBUG)
endif()

include_directories(${PROJECT_SOURCE_DIR}/extern/spdlog/include/)
include_directories(${PROJECT_SOURCE_DIR}/extern/json/include/nlohmann)
include_directories(${PROJECT_SOURCE_DIR}/src/)


file(GLOB 
        SOURCES "src/core/*.cpp")

add_library(${PROJECT_NAME} SHARED ${SOURCES})
set_target_properties(${PROJECT_NAME} 
							PROPERTIES 
								LINKER_LANGUAGE CXX
								PUBLIC_HEADER 	"rubyvn.hpp")

generate_export_header(${PROJECT_NAME} 
							BASE_NAME 			${PROJECT_NAME}
							EXPORT_MACRO_NAME 	${DLL_EXPORT_MACRO}
							EXPORT_FILE_NAME 	"src/ruby.hpp")

