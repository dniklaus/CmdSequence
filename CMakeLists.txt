cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

option(BUILD_TESTING "Build unit tests" ON)

set(PROJECT "pos")
project(${PROJECT} VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(BUILD_TESTING)
    enable_testing()
    add_subdirectory(test)
endif()

# Names of needed components
set(TARGET ${PROJECT})
set(INCLUDE_DIRECTORIES ".")
set(SOURCES
	Cmd.cpp
	CmdAdapter.cpp
  CmdSeqTimer.cpp
  CmdSequence.cpp
)
# Make the library
add_library(${TARGET} STATIC ${SOURCES})
target_compile_options(${TARGET} PRIVATE -Wall -Wextra -Wpedantic)
target_link_libraries(${TARGET})
target_include_directories(${TARGET} PUBLIC ${INCLUDE_DIRECTORIES})