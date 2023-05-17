cmake_minimum_required(VERSION 3.7)

set(UNIT_TEST_LIST smap)

foreach(NAME IN LISTS UNIT_TEST_LIST)
  list(APPEND UNIT_TEST_SOURCE_LIST
    ${NAME}.test.cpp)
endforeach()
 
get_filename_component(PROJ_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
set(TARGET_NAME ${PROJ_NAME})
 
add_executable(${TARGET_NAME}
  ../smap/src/smap.c
  main.cpp
  ${UNIT_TEST_SOURCE_LIST})
 
include_directories(
  ../smap/src
  )

add_test(
  NAME ${TARGET_NAME}
  COMMAND ${TARGET_NAME} -o report.xml -r junit)