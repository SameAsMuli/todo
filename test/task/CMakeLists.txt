include(GoogleTest)

file(GLOB SOURCES *.cpp)

add_executable(task_tests ${SOURCES})
target_link_libraries(task_tests gtest_main task)

gtest_discover_tests(task_tests TEST_LIST task_test_list)
