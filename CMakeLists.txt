cmake_minimum_required(VERSION 3.10)

project(CopyCat C)

set(CMAKE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/src/*.c ${CMAKE_SOURCE_DIR}/main.c)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include)
