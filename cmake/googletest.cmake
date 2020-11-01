# Macro to download and unpack Google Test at configure time
macro(fetch_googletest)
  configure_file(
    ${PROJECT_SOURCE_DIR}/cmake/googletest.cmake.in
    ${PROJECT_BINARY_DIR}/googletest/CMakeLists.txt
  )

  # Download and configure Google Test
  execute_process(
    COMMAND           "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" .
    RESULT_VARIABLE   result
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/googletest
  )

  if(result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
  endif()

  # Build Google Test
  execute_process(
    COMMAND           "${CMAKE_COMMAND}" --build .
    RESULT_VARIABLE   result
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/googletest
  )

  if(result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
  endif()

  # Adds the targets: gtest, gtest_main, gmock, gmock_main
  add_subdirectory(
    ${PROJECT_BINARY_DIR}/googletest-src
    ${PROJECT_BINARY_DIR}/googletest-build
    EXCLUDE_FROM_ALL
  )
endmacro()
