cmake_minimum_required(VERSION 3.14)
project(Chessqdl)

add_subdirectory(src)
add_subdirectory(test)

set(CMAKE_CXX_STANDARD 17)


add_executable(Chessqdl src/main.cpp src/game.cpp src/game.h src/board.cpp src/board.h src/tile.cpp src/tile.h src/piece.cpp src/piece.h src/Engine/bitboard.cpp src/Engine/bitboard.h)

find_package(SFML 2.5.1 REQUIRED graphics network audio window system)

target_link_libraries(Chessqdl sfml-graphics sfml-audio sfml-window)

