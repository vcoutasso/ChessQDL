cmake_minimum_required(VERSION 3.10)
project(ChessQDL)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(${CMAKE_PROJECT_NAME} ${SOURCE_FILES})

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
    enable_testing()
    add_subdirectory(tests)
elseif (CMAKE_BUILD_TYPE MATCHES Release)
    message("CMake in Release mode")
endif ()

# Include external libraries
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE libs/cxxopts/include include)

# Link ChessQDL libraries
target_link_libraries(${CMAKE_PROJECT_NAME} ${CMAKE_PROJECT_NAME}_lib)

if (CMAKE_BUILD_TYPE MATCHES Release)
    add_custom_command(TARGET ${CMAKE_PROJECT_NAME}
            POST_BUILD
            COMMAND strip -s bin/${CMAKE_PROJECT_NAME})
endif ()
