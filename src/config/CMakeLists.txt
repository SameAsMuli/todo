add_library(config)

file(GLOB SOURCE_FILES *.cpp)
file(GLOB HEADER_FILES *.hpp)

configure_file(version.hpp.in ${CMAKE_BINARY_DIR}/gen/version.hpp)

target_sources(
  config
  PRIVATE  ${SOURCE_FILES}
  PUBLIC   ${HEADER_FILES}
)

target_include_directories(
  config
  PUBLIC ${CMAKE_BINARY_DIR} ${PROJECT_SOURCE_DIR}/src
)
