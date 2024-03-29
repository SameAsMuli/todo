cmake_minimum_required(VERSION 3.7)

# Define Project
project(
  todo
  LANGUAGES  CXX
  VERSION    0.5.0
)

# Generate compile_commands.json(used for clang tooling integration)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Enable ccache if available
find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
  set(CMAKE_CXX_COMPILER_LAUNCHER ccache)
endif(CCACHE_FOUND)

# Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include SafeInt
include(cmake/safeint.cmake)
fetch_safeint()

# Define binary and how to build it
add_subdirectory(src/action)
add_subdirectory(src/config)
add_subdirectory(src/error)
add_subdirectory(src/file)
add_subdirectory(src/input)
add_subdirectory(src/task)
add_subdirectory(src/util)

add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE action task file input util error config)

target_include_directories(${PROJECT_NAME} PUBLIC src)

target_compile_options(${PROJECT_NAME} PUBLIC -std=c++17 -g -O0 -pedantic -Wall
  -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization
  -Wformat=2 -Winit-self -Wmissing-include-dirs -Woverloaded-virtual
  -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-overflow=5
  -Wundef -Wswitch-default -Werror -Wno-unused)

# Include Google Test
include(cmake/googletest.cmake)
fetch_googletest()

# Include tests
enable_testing()
add_subdirectory(test)

# Define how to install binary
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
