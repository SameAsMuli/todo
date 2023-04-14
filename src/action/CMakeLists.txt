add_library(action)

file(GLOB SOURCE_FILES *.cpp)
file(GLOB HEADER_FILES *.hpp)

target_sources(
  action
  PRIVATE ${SOURCE_FILES}
  PUBLIC ${HEADER_FILES})

target_include_directories(action PUBLIC ${PROJECT_SOURCE_DIR}/src)

target_compile_options(action PUBLIC $<$<CONFIG:Debug>: -g3>
                                     $<$<CONFIG:Release>: -O3>)
