#include <sstream> // std::stringstream

#include "task/task.hpp"
#include "gtest/gtest.h"

#define TaskStreamTest()                                                       \
    todo::task::Task task;                                                     \
    std::stringstream ss_in{expected_string};                                  \
    std::stringstream ss_out;                                                  \
    ss_in >> task;                                                             \
    ss_out << task;                                                            \
    EXPECT_EQ(expected_string, ss_out.str());

/* Test all public methods */
TEST(TaskStream, Simple) {
    std::string expected_string{"normal;1602092528;;0;Run the test"};
    TaskStreamTest();
}

TEST(TaskStream, PreviousPrefix) {
    std::string expected_string{"done;1602092528;urgent;0;Run the test"};
    TaskStreamTest();
}

TEST(TaskStream, UnusualCharacters) {
    std::string expected_string{
        "low;1602092538;;0;Use awkward characters; like this '-' and \"!\""};
    TaskStreamTest();
}
