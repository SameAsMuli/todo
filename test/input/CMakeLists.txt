include(GoogleTest)

file(GLOB SOURCES *.cpp)

add_executable(input_tests ${SOURCES})
target_link_libraries(input_tests gtest_main input util)

gtest_discover_tests(input_tests TEST_LIST input_test_list)
