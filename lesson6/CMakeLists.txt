CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(lesson6)

file(GLOB SOURCES "src/*.cpp")

add_executable(lesson6 ${SOURCES})

target_include_directories(lesson6 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

