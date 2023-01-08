add_library(util)

file(GLOB SOURCE_FILES *.cpp)
file(GLOB HEADER_FILES *.hpp)

target_sources(
  util
  PRIVATE  ${SOURCE_FILES}
  PUBLIC   ${HEADER_FILES}
)

target_include_directories(
  util
  PUBLIC ${PROJECT_SOURCE_DIR}/src
)

target_compile_options(util PUBLIC
    $<$<CONFIG:Debug>: -g3>
    $<$<CONFIG:Release>: -O3>)
