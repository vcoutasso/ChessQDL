cmake_minimum_required(VERSION 3.10)
project(${CMAKE_PROJECT_NAME}_lib)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES Engine/bitboard.cpp Engine/movegen.cpp
        Engine/engine.cpp Engine/utils.cpp)

set(HEADER_FILES Engine/bitboard.hpp Engine/const.hpp Engine/movegen.hpp
		Engine/engine.hpp Engine/utils.hpp argparser.hpp)


# The library contains header and source files.
add_library(${PROJECT_NAME} STATIC
		${SOURCE_FILES}
		${HEADER_FILES}
		)

# Otherwise the library would be named libChessQDL_lib.a
SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES PREFIX "")

if (CMAKE_BUILD_TYPE MATCHES Debug)
	target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wunreachable-code -g -O0)
else ()
	target_compile_options(${PROJECT_NAME} PRIVATE -O2)
endif ()
