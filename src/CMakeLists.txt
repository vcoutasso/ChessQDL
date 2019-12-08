project(${CMAKE_PROJECT_NAME}_lib)

set(SOURCE_FILES Engine/bitboard.cpp Engine/movegen.cpp
		GUI/board.cpp GUI/game.cpp GUI/piece.cpp GUI/tile.cpp
        Engine/engine.cpp)

set(HEADER_FILES Engine/bitboard.h Engine/const.h Engine/movegen.h
		GUI/board.h GUI/game.h GUI/piece.h GUI/tile.h
        Engine/engine.h)


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
