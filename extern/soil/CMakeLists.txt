cmake_minimum_required(VERSION 3.13)
project("soil")

add_library(${PROJECT_NAME} STATIC 
        "src/soil.c"
        "src/image_dxt.c" 
        "src/image_helper.c" 
        "src/stb_image_aug.c")
target_include_directories(${PROJECT_NAME} PUBLIC include/)