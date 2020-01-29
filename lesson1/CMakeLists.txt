CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(lesson1)

set(SOURCES src/lesson1.cpp)

add_executable(lesson1 ${SOURCES})

target_include_directories(lesson1 PRIVATE include)


