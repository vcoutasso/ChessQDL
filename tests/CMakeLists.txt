cmake_minimum_required(VERSION 3.23)
project(${CMAKE_PROJECT_NAME}_tests)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_CURRENT_BINARY_DIR}/googletest-src/googlemock/include)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/googletest-src/googletest/include)

# Bitboard tests
set(SOURCE_FILES bitboard_tests.cpp)
set(TEST_NAME bitboard_tests)

add_executable(${TEST_NAME} ${SOURCE_FILES})
add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
target_link_libraries(${TEST_NAME} ${CMAKE_PROJECT_NAME}_lib gtest gtest_main)

# Move generator tests
set(SOURCE_FILES movegen_tests.cpp)
set(TEST_NAME move_generator_tests)

add_executable(${TEST_NAME} ${SOURCE_FILES})
add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
target_link_libraries(${TEST_NAME} ${CMAKE_PROJECT_NAME}_lib gtest gtest_main)

