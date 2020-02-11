cmake_minimum_required(VERSION 3.10)
project(${CMAKE_PROJECT_NAME}_tests)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_CURRENT_BINARY_DIR}/googletest-src/googlemock/include)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/googletest-src/googletest/include)

set(SOURCE_FILES bitboard_tests.cpp movegen_tests.cpp)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} ${CMAKE_PROJECT_NAME}_lib gtest gtest_main)
