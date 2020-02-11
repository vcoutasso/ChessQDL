cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)

project(${CMAKE_PROJECT_NAME}_lib)

set(SOURCE_FILES Engine/bitboard.cpp Engine/movegen.cpp
        Engine/engine.cpp Engine/utils.cpp)

set(HEADER_FILES Engine/bitboard.h Engine/const.h Engine/movegen.h
        Engine/engine.h Engine/utils.h)


# The library contains header and source files.
add_library(${CMAKE_PROJECT_NAME}_lib STATIC
		${SOURCE_FILES}
		${HEADER_FILES}
		)


if (CMAKE_BUILD_TYPE MATCHES Debug)
	target_compile_options(${CMAKE_PROJECT_NAME}_lib PUBLIC -Wall -Wextra -Wunreachable-code -g -O0)
else()
	target_compile_options(${CMAKE_PROJECT_NAME}_lib PUBLIC -O2)
endif()
