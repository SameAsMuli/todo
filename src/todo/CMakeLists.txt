add_library(todo_lib)

file(GLOB SOURCE_FILES *.cpp)
file(GLOB HEADER_FILES *.hpp)

target_sources(
  todo_lib
  PRIVATE  ${SOURCE_FILES}
  PUBLIC   ${HEADER_FILES}
)

target_include_directories(
  todo_lib
  PUBLIC ${PROJECT_SOURCE_DIR}/src
)
