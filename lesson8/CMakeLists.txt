CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(lesson8)

file(GLOB SOURCES "src/*.cpp")

add_executable(lesson8 ${SOURCES})

target_include_directories(lesson8 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

