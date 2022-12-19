PROJ_NAME=ChessQDL

all: release

release:
	@ mkdir build; cd build; cmake ..; make

debug:
	@ mkdir build; cd build; cmake -DCMAKE_BUILD_TYPE=Debug ..; make

run:
	@ ./build/bin/$(PROJ_NAME)

test:
	@ ctest -V

remake: clean all

clean:
	@ rm -rf build
