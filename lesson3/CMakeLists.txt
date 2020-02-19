CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(lesson3)

file(GLOB SOURCES "src/*.cpp")

add_executable(lesson3 ${SOURCES})

target_include_directories(lesson3 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
