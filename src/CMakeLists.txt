project(${CMAKE_PROJECT_NAME}_lib)

set(HEADER_FILES Engine/bitboard.cpp Engine/chessqdl.cpp Engine/movegen.cpp
		GUI/board.cpp GUI/game.cpp GUI/piece.cpp GUI/tile.cpp
)

set(SOURCE_FILES Engine/bitboard.h Engine/chessqdl.h Engine/movegen.h
		GUI/board.h GUI/game.h GUI/piece.h GUI/tile.h
)

# The library contains header and source files.
add_library(${CMAKE_PROJECT_NAME}_lib STATIC
		${SOURCE_FILES}
		${HEADER_FILES}
		)



