add_library(input)

file(GLOB SOURCE_FILES *.cpp)
file(GLOB HEADER_FILES *.hpp)

target_sources(
  input
  PRIVATE  ${SOURCE_FILES}
  PUBLIC   ${HEADER_FILES}
)

target_include_directories(
  input
  PUBLIC ${PROJECT_SOURCE_DIR}/src
)

target_compile_options(input PUBLIC -g)
