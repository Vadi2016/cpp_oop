CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(lesson5)

file(GLOB SOURCES "src/*.cpp")

add_executable(lesson5 ${SOURCES})

target_include_directories(lesson5 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
