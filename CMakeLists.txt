cmake_minimum_required(VERSION 3.11.0)
project(ChessTD VERSION 0.1.0)

enable_language(CXX)

# use C++ standard version 17
set(CMAKE_CXX_STANDARD 17)
# produce non-optimized code with debug symbols
set(CMAKE_BUILD_TYPE Debug)

message(STATUS "BUILD directory is ${CMAKE_BINARY_DIR}")
message(STATUS "SRC directory is ${CMAKE_SOURCE_DIR}")

# Add all .c, - files under src/ directory
file(GLOB SOURCES_C "src/*.c")
# Add all .cpp, - files under src/ directory
file(GLOB SOURCES_CPP "src/*.cpp")
# Add all .hpp, - files under src/ directory
file(GLOB SOURCES_HPP "src/*.hpp")
# Add all .h, - files under src/ directory
file(GLOB SOURCES_H "src/*.h")
# Add all .cpp, - files under test/ directory
file(GLOB TESTSOURCES_CPP "tests/*.cpp")

file(GLOB ENEMIES_CPP "src/enemies/*.cpp")
file(GLOB ENEMIES_HPP "src/enemies/*.hpp")
file(GLOB TOWERS_CPP "src/towers/*.cpp")
file(GLOB TOWERS_HPP "src/towers/*.hpp")
file(GLOB TILES_CPP "src/tiles/*.cpp")
file(GLOB TILES_HPP "src/tiles/*.hpp")
file(GLOB GUISOURCES_HPP "src/GUI/*.hpp")
file(GLOB GUISOURCES_CPP "src/GUI/*.cpp")

set(SOURCES ${SOURCES_C} ${SOURCES_CPP} ${SOURCES_H} ${SOURCES_HPP} ${ENEMIES_CPP} ${ENEMIES_HPP} ${TOWERS_CPP} ${TOWERS_HPP} ${TILES_CPP} ${TILES_HPP} ${GUISOURCES_CPP} ${GUISOURCES_HPP})
set(TESTSOURCES ${TESTSOURCES_CPP} ${ENEMIES_CPP} ${ENEMIES_HPP} ${TOWERS_CPP} ${TOWERS_HPP} ${TILES_CPP} ${TILES_CPP} ${TILES_HPP} ${GUISOURCES_CPP} ${GUISOURCES_HPP})

message(STATUS "SRC directory source code files: \n\t-- HEADERS: ${SOURCES_H}${SOURCES_HPP}\n\t-- C SOURCES: ${SOURCES_C}\n\t-- CPP SOURCE:${SOURCES_CPP}\n\t-- ALL:${SOURCES}")
message(STATUS "TEST source code files: \n\t-- ALL:${TESTSOURCES}")
# add the executable target
add_executable(ChessTD)
add_executable(Test)

# include SFML
find_package(SFML 2.5 COMPONENTS window system network audio graphics REQUIRED)
target_link_libraries(ChessTD PUBLIC sfml-system sfml-graphics sfml-audio sfml-network sfml-window)
target_link_libraries(Test PUBLIC sfml-system sfml-graphics sfml-audio sfml-network sfml-window)

# add sources to executables
target_sources(ChessTD PUBLIC ${SOURCES})
target_include_directories(ChessTD PUBLIC .)
target_include_directories(ChessTD PUBLIC src)
target_sources(Test PUBLIC ${TESTSOURCES})
target_include_directories(Test PUBLIC tests)
target_include_directories(Test PUBLIC .)
target_include_directories(Test PUBLIC src)

# get a lot of warnings
if(MSVC)
    target_compile_options(ChessTD PRIVATE /Wall)
else()
    # gcc and clang
    target_compile_options(ChessTD PRIVATE -Wall -Wextra -pedantic -Wno-missing-field-initializers)
endif()