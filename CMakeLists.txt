cmake_minimum_required(VERSION 3.11)

# Define Project
project(
  todo
  LANGUAGES  CXX
  VERSION    1.0.0
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

# Include required dependencies
include(FetchContent)

FetchContent_Declare(
  date
  GIT_REPOSITORY https://github.com/HowardHinnant/date.git
  GIT_TAG        v3.0.1
)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.12.1
)

FetchContent_Declare(
  json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG        v3.10.5
)

FetchContent_MakeAvailable(date googletest json)
include_directories(
    SYSTEM
    ${date_SOURCE_DIR}/include
    ${json_SOURCE_DIR}/include
)

# Define binary and how to build it
add_subdirectory(src/action)
add_subdirectory(src/config)
add_subdirectory(src/file)
add_subdirectory(src/input)
add_subdirectory(src/task)
add_subdirectory(src/util)

add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE action task file input util config)

target_include_directories(${PROJECT_NAME} PUBLIC src)

target_compile_options(${PROJECT_NAME} PUBLIC -std=c++17 -pedantic -Wall
  -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization
  -Wformat=2 -Winit-self -Wmissing-include-dirs -Woverloaded-virtual
  -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-overflow=5
  -Wundef -Wswitch-default -Werror -Wno-unused
  $<$<CONFIG:Debug>: -g3>
  $<$<CONFIG:Release>: -O3>)

# Generate a tags file if ctags is available
find_program(CTAGS_FOUND ctags)
if(CTAGS_FOUND)
    set_source_files_properties(tags PROPERTIES GENERATED true)
    add_custom_target(
        tags
        COMMAND ctags -R --c++-kinds=+p --fields=+iaS --extras=+q --language-force=C++
            ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}
        COMMAND ln -sf ${CMAKE_CURRENT_BINARY_DIR}/tags ${PROJECT_SOURCE_DIR}/.tags
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    )
    add_dependencies(${PROJECT_NAME} tags)
endif(CTAGS_FOUND)

# Create link to compile_commands.json in project root
add_custom_target(
    compile_commands
    COMMAND ln -sf ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json
        ${PROJECT_SOURCE_DIR}/compile_commands.json
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)
add_dependencies(${PROJECT_NAME} compile_commands)

# Ensure git hooks are installed
add_custom_target(
    git_hooks
    COMMAND git config core.hooksPath ${PROJECT_SOURCE_DIR}/.githooks
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)
add_dependencies(${PROJECT_NAME} git_hooks)

# Include tests
enable_testing()
add_subdirectory(test)

# Define how to install binary
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
