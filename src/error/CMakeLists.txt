add_library(error)

file(GLOB SOURCE_FILES *.cpp)
file(GLOB HEADER_FILES *.hpp)

target_sources(
  error
  PRIVATE  ${SOURCE_FILES}
  PUBLIC   ${HEADER_FILES}
)

target_include_directories(
  error
  PUBLIC ${PROJECT_SOURCE_DIR}/src
)
