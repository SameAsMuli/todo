# Macro to download and unpack SafeInt at configure time
macro(fetch_safeint)
  configure_file(
    ${PROJECT_SOURCE_DIR}/cmake/safeint.cmake.in
    ${PROJECT_BINARY_DIR}/safeint/CMakeLists.txt
  )

  # Download and configure SafeInt
  execute_process(
    COMMAND           "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" .
    RESULT_VARIABLE   result
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/safeint
  )

  if(result)
    message(FATAL_ERROR "CMake step for safeint failed: ${result}")
  endif()

  # Build SafeInt
  execute_process(
    COMMAND           "${CMAKE_COMMAND}" --build .
    RESULT_VARIABLE   result
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/safeint
  )

  if(result)
    message(FATAL_ERROR "Build step for safeint failed: ${result}")
  endif()

  # Adds the directory to the include path
  include_directories(${PROJECT_BINARY_DIR}/safeint-src)
endmacro()
