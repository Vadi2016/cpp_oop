CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(lesson4)

file(GLOB SOURCES "src/*.cpp")

add_executable(lesson4 ${SOURCES})

target_include_directories(lesson4 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
