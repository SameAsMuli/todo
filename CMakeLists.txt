cmake_minimum_required(VERSION 3.4)

# Define Project
project(
  todo
  LANGUAGES  CXX
  VERSION    0.4.0
)

# Enable ccache if available
find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
  set(CMAKE_CXX_COMPILER_LAUNCHER ccache)
endif(CCACHE_FOUND)

# Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find all source files
file(GLOB_RECURSE SOURCES src/*.cpp)

# Define binary and how to build it
add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC src)

target_compile_options(${PROJECT_NAME} PUBLIC -std=c++17 -g -pedantic -Wall
  -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization
  -Wformat=2 -Winit-self -Wmissing-include-dirs -Wold-style-cast
  -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo
  -Wstrict-overflow=5 -Wundef -Wswitch-default -Werror -Wno-unused)

# Define how to install binary
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
