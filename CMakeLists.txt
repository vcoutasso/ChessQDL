cmake_minimum_required(VERSION 3.14)
project(Chessqdl)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5.1 REQUIRED graphics network audio window system)

set(SOURCE_FILES main.cpp)

add_executable(${CMAKE_PROJECT_NAME}_run ${SOURCE_FILES})

include_directories(src)

add_subdirectory(src)

if (CMAKE_BUILD_TYPE MATCHES Debug)
	message("CMake in Debug mode")
	# Download and unpack googletest at configure time
	configure_file(tests/CMakeLists.txt.in tests/googletest-download/CMakeLists.txt)
	execute_process(COMMAND "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" .
			WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/tests/googletest-download"
			)
	execute_process(COMMAND "${CMAKE_COMMAND}" --build .
			WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/tests/googletest-download"
			)

	# Prevent GoogleTest from overriding our compiler/linker options
	# when building with Visual Studio
	set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

	# Add googletest directly to our build. This adds the following targets:
	# gtest, gtest_main, gmock and gmock_main
	add_subdirectory("${CMAKE_BINARY_DIR}/tests/googletest-src"
			"${CMAKE_BINARY_DIR}/tests/googletest-build"
			)

	# The gtest/gmock targets carry header search path dependencies
	# automatically when using CMake 2.8.11 or later. Otherwise we
	# have to add them here ourselves.
	if (CMAKE_VERSION VERSION_LESS 2.8.11)
		include_directories("${gtest_SOURCE_DIR}/include"
				"${gmock_SOURCE_DIR}/include"
				)
	endif ()
	enable_testing()
	add_subdirectory(tests)
elseif (CMAKE_BILD_TYPE MATCHES Release)
	message("CMake in Release mode")
endif ()


target_link_libraries(${CMAKE_PROJECT_NAME}_run ${CMAKE_PROJECT_NAME}_lib sfml-graphics sfml-audio sfml-window)

if (CMAKE_BUILD_TYPE MATCHES Release)
	add_custom_command(TARGET ${CMAKE_PROJECT_NAME}_run
			POST_BUILD
			COMMAND strip -s ${CMAKE_PROJECT_NAME}_run)
endif()

