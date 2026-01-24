cmake_minimum_required(VERSION 3.23)
project(${CMAKE_PROJECT_NAME}_tests)

set(CMAKE_CXX_STANDARD 17)

# GoogleTest includes are available via FetchContent
# The googletest_SOURCE_DIR is set by FetchContent in parent CMakeLists.txt
include_directories(${googletest_SOURCE_DIR}/googlemock/include)
include_directories(${googletest_SOURCE_DIR}/googletest/include)

# Bitboard tests
set(SOURCE_FILES bitboard_tests.cpp)
set(TEST_NAME bitboard_tests)

add_executable(${TEST_NAME} ${SOURCE_FILES})
add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
target_link_libraries(${TEST_NAME} ${CMAKE_PROJECT_NAME}_lib gtest_main)

# Move generator tests
set(SOURCE_FILES movegen_tests.cpp)
set(TEST_NAME move_generator_tests)

add_executable(${TEST_NAME} ${SOURCE_FILES})
add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
target_link_libraries(${TEST_NAME} ${CMAKE_PROJECT_NAME}_lib gtest_main)

# Checkmate and stalemate tests
set(SOURCE_FILES checkmate_tests.cpp)
set(TEST_NAME checkmate_tests)

add_executable(${TEST_NAME} ${SOURCE_FILES})
add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
target_link_libraries(${TEST_NAME} ${CMAKE_PROJECT_NAME}_lib gtest_main gmock)

# Chess rules comprehensive tests
set(SOURCE_FILES chess_rules_tests.cpp)
set(TEST_NAME chess_rules_tests)

add_executable(${TEST_NAME} ${SOURCE_FILES})
add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
target_link_libraries(${TEST_NAME} ${CMAKE_PROJECT_NAME}_lib gtest_main gmock)

