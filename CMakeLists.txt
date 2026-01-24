cmake_minimum_required(VERSION 3.23)

project(ChessQDL)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp)

# All build artifacts and dependencies go into build/ directory
# This allows easy cleanup: make clean removes artifacts, make clean-all nukes everything
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)

set(FETCHCONTENT_QUIET FALSE)
# Store downloaded dependencies in build/_deps (inside build directory for easy cleanup)
set(FETCHCONTENT_BASE_DIR "${CMAKE_BINARY_DIR}/_deps")

fetchcontent_declare(
        cxxopts
        GIT_REPOSITORY https://github.com/jarro2783/cxxopts.git
        GIT_TAG v3.0.0
        GIT_PROGRESS TRUE
)

if(NOT cxxopts_POPULATED)
    fetchcontent_populate(cxxopts)
    add_subdirectory(${cxxopts_SOURCE_DIR} ${cxxopts_BUILD_DIR})
endif()

add_executable(${CMAKE_PROJECT_NAME} ${SOURCE_FILES})

include_directories(src)
add_subdirectory(src)

if (CMAKE_BUILD_TYPE MATCHES Debug)
    message("CMake in Debug mode")
    
    # Use FetchContent for googletest (simpler and cleaner than ExternalProject)
    # Downloads to .deps directory to avoid repeated downloads
    fetchcontent_declare(
            googletest
            GIT_REPOSITORY https://github.com/google/googletest.git
            GIT_TAG release-1.12.1
            GIT_PROGRESS TRUE
    )
    
    # Prevent GoogleTest from overriding our compiler/linker options
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    
    # Fetch and populate googletest
    fetchcontent_makeavailable(googletest)
    
    enable_testing()
    add_subdirectory(tests)
elseif (CMAKE_BUILD_TYPE MATCHES Release)
    message("CMake in Release mode")
endif ()

# Include libraries
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE include)

# Link ChessQDL libraries
target_link_libraries(${CMAKE_PROJECT_NAME} cxxopts)
target_link_libraries(${CMAKE_PROJECT_NAME} ${CMAKE_PROJECT_NAME}_lib)

if (CMAKE_BUILD_TYPE MATCHES Release)
    # Strip the binary in a platform-independent way
    if(APPLE)
        add_custom_command(TARGET ${CMAKE_PROJECT_NAME}
                POST_BUILD
                COMMAND xcrun strip -x ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_PROJECT_NAME})
    else()
        add_custom_command(TARGET ${CMAKE_PROJECT_NAME}
                POST_BUILD
                COMMAND strip ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_PROJECT_NAME})
    endif()
endif ()
