# Macro to download and unpack Howard Hinnant's Date library at configure time
macro(fetch_date)
  configure_file(
    ${PROJECT_SOURCE_DIR}/cmake/date.cmake.in
    ${PROJECT_BINARY_DIR}/date/CMakeLists.txt
  )

# Download and configure Date library
  execute_process(
    COMMAND           "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" .
    RESULT_VARIABLE   result
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/date
  )

  if(result)
    message(FATAL_ERROR "CMake step for date failed: ${result}")
  endif()

  # Build Date library
  execute_process(
    COMMAND           "${CMAKE_COMMAND}" --build .
    RESULT_VARIABLE   result
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/date
  )

  if(result)
    message(FATAL_ERROR "Build step for date failed: ${result}")
  endif()

  # Adds the directory to the include path
  include_directories(${PROJECT_BINARY_DIR}/date-src/include)
endmacro()
