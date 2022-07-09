include(GoogleTest)

file(GLOB SOURCES *.cpp)

add_executable(util_tests ${SOURCES})
target_link_libraries(util_tests gmock_main gtest_main util)

gtest_discover_tests(util_tests TEST_LIST util_test_list)
