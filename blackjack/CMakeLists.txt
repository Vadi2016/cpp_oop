CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(Blackjack)

file(GLOB SOURCES "src/*.cpp")

add_executable(Blackjack ${SOURCES})

target_include_directories(Blackjack PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

