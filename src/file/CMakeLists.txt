add_library(file)

file(GLOB SOURCE_FILES *.cpp)
file(GLOB HEADER_FILES *.hpp)

target_sources(
  file
  PRIVATE  ${SOURCE_FILES}
  PUBLIC   ${HEADER_FILES}
)

target_include_directories(
  file
  PUBLIC ${PROJECT_SOURCE_DIR}/src
)

target_compile_options(file PUBLIC -g)
