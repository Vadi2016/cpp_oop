CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(lesson2)

file(GLOB SOURCES "src/*.cpp")

add_executable(lesson2 ${SOURCES})

target_include_directories(lesson2 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)



