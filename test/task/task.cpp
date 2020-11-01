#include <sstream> // std::stringstream

#include "task/task.hpp"
#include "gtest/gtest.h"

#define TaskStreamTest(string)                                                 \
    todo::task::Task task;                                                     \
    std::stringstream ss_in{s};                                                \
    std::stringstream ss_out;                                                  \
    ss_in >> task;                                                             \
    ss_out << task;                                                            \
    EXPECT_EQ(ss_out.str(), s);

/* Test all public methods */
TEST(TaskStream, Simple) {
    std::string s{"1602092528; ;0;- Run the test"};
    TaskStreamTest();
}

TEST(TaskStream, UnusualCharacters) {
    std::string s{
        "1602092538; ;0;~ Use awkward characters; like this '-' and '!'"};
    TaskStreamTest();
}
