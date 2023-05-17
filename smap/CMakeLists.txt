cmake_minimum_required(VERSION 3.7)

get_filename_component(PROJ_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${PROJ_NAME})

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_C_FLAGS "-Wall -Wextra -pedantic")
set(CMAKE_C_FLAGS_DEBUG "-g -fsanitize=address")
set(CMAKE_C_FLAGS_RELEASE "-O3")


set(SOURCE_FILES
        src/smap.c
        src/smap.h
        src/main.c
    )

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
