PROJ_NAME=ChessQDL

all: release

release:
	@ mkdir build; cd build; cmake ..; make

debug:
	@ mkdir build; cd build; cmake -DCMAKE_BUILD_TYPE=Debug ..; make

compile_commands:
	@ cd build; cmake .. -DCMAKE_EXPORT_COMPILE_COMMANDS=1

run:
	@ ./build/bin/$(PROJ_NAME)

test:
	@ cd build; ctest -V

remake: clean all

clean:
	@ rm -rf build
