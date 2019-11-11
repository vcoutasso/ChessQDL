cmake_minimum_required(VERSION 3.14)
project(Chessqdl)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5.1 REQUIRED graphics network audio window system)

set(SOURCE_FILES main.cpp)
add_executable(${CMAKE_PROJECT_NAME}_run ${SOURCE_FILES})

include_directories(src)

add_subdirectory(src)
add_subdirectory(tests)

target_link_libraries(${CMAKE_PROJECT_NAME}_run ${CMAKE_PROJECT_NAME}_lib sfml-graphics sfml-audio sfml-window)

