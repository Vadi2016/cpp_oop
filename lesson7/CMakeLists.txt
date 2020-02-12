CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(lesson7)

file(GLOB SOURCES "src/*.cpp")

add_executable(lesson7 ${SOURCES})

target_include_directories(lesson7 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

