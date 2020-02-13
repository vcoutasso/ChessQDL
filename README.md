# ChessQDL

Final project of the Data Structures 1 subject. Presented on 12/2019.



ChessQDL is a chess engine that uses a simple heuristic function to evaluate the current state of a given board and the minimax algorithm to choose a move within the tree of possible moves.

The engine was designed to allow for games of Human vs Machine. Currently it's only possible to play as white pieces against the engine's black pieces.



## Build instructions

Create the build directory:

```
$ mkdir build
$ cd build
```

Build Release version:

```
$ cmake ..
$ make
```

Build Debug version:

```
$ cmake -DCMAKE_BUILD_TYPE=Debug ..
$ make
```

Note: Building in Debug mode will download Google Test from Github.

As an alternative to Unix Makefiles, other generators such as Ninja can be used:

```
$ cmake -G "Ninja" ..
$ ninja
```

Run tests (Debug version):

```
$ ctest -V
```

Build Doxygen documentation:

```
$ cd docs
$ doxygen
```

## License

This software is free to use under the MIT License. See [this reference](https://choosealicense.com/licenses/mit/) for more information.
