add_library(task)

file(GLOB SOURCE_FILES *.cpp)
file(GLOB HEADER_FILES *.hpp)

target_sources(
  task
  PRIVATE ${SOURCE_FILES}
  PUBLIC ${HEADER_FILES})

target_include_directories(task PUBLIC ${PROJECT_SOURCE_DIR}/src)

target_compile_options(task PUBLIC $<$<CONFIG:Debug>: -g3> $<$<CONFIG:Release>:
                                   -O3>)
