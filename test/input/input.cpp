#include "input/input.hpp"
#include "gtest/gtest.h"

/* Fixture class to test each public method */
class InputMethods : public ::testing::Test {
  public:
    InputMethods()
        : n0(1, a0), n1(2, a1), n2(3, a2), n3(4, a3), n4(5, a4), n5(5, a5),
          n6(5, a6), n7(5, a7), n8(5, a8), n9(6, a9), n10(6, a10), n11(6, a11),
          n12(6, a12), n13(6, a13), n14(6, a14), n15(6, a15), n16(6, a16),
          n17(6, a17), n18(6, a18), n19(6, a19), n20(6, a20), n21(6, a21),
          n22(6, a22), n23(6, a23), n24(6, a24) {}

  protected:
    char const *a0[1] = {"todo"};
    char const *a1[2] = {"todo", "action"};
    char const *a2[3] = {"todo", "action", "first argument"};
    char const *a3[4] = {"todo", "action", "first argument", "2nd"};
    char const *a4[5] = {"todo", "action", "--global", "first argument", "2nd"};
    char const *a5[5] = {"todo", "action", "--rubbish", "first argument",
                         "2nd"};
    char const *a6[5] = {"todo", "action", "first argument", "--global", "2nd"};
    char const *a7[5] = {"todo", "--global", "action", "first argument", "2nd"};
    char const *a8[5] = {"todo", "--rubbish", "action", "first argument",
                         "2nd"};
    char const *a9[6] = {"todo",  "action",         "--global",
                         "--all", "first argument", "2nd"};
    char const *a10[6] = {"todo",           "action", "--global",
                          "first argument", "--all",  "2nd"};
    char const *a11[6] = {"todo",  "--global",       "action",
                          "--all", "first argument", "2nd"};
    char const *a12[6] = {"todo",           "--global", "action",
                          "first argument", "--all",    "2nd"};
    char const *a13[6] = {"todo",      "action",         "--global",
                          "--rubbish", "first argument", "2nd"};
    char const *a14[6] = {"todo",           "action",    "--global",
                          "first argument", "--rubbish", "2nd"};
    char const *a15[6] = {"todo",      "--global",       "action",
                          "--rubbish", "first argument", "2nd"};
    char const *a16[6] = {"todo",           "--global",  "action",
                          "first argument", "--rubbish", "2nd"};
    char const *a17[6] = {"todo",     "action",         "--rubbish",
                          "--global", "first argument", "2nd"};
    char const *a18[6] = {"todo",           "action",   "--rubbish",
                          "first argument", "--global", "2nd"};
    char const *a19[6] = {"todo",     "--rubbish",      "action",
                          "--global", "first argument", "2nd"};
    char const *a20[6] = {"todo",           "--rubbish", "action",
                          "first argument", "--global",  "2nd"};
    char const *a21[6] = {"todo",     "action",         "--",
                          "--global", "first argument", "2nd"};
    char const *a22[6] = {"todo", "action",   "first argument",
                          "--",   "--global", "2nd"};
    char const *a23[6] = {"todo",           "--", "action", "--global",
                          "first argument", "2nd"};
    char const *a24[6] = {"todo", "action", "--global",
                          "--",   "--all",  "first argument"};
    input::Input n0;
    input::Input n1;
    input::Input n2;
    input::Input n3;
    input::Input n4;
    input::Input n5;
    input::Input n6;
    input::Input n7;
    input::Input n8;
    input::Input n9;
    input::Input n10;
    input::Input n11;
    input::Input n12;
    input::Input n13;
    input::Input n14;
    input::Input n15;
    input::Input n16;
    input::Input n17;
    input::Input n18;
    input::Input n19;
    input::Input n20;
    input::Input n21;
    input::Input n22;
    input::Input n23;
    input::Input n24;
};

/* Test all public methods */
TEST_F(InputMethods, GetAction) {
    EXPECT_EQ(n0.getAction(), "");
    EXPECT_EQ(n1.getAction(), "action");
    EXPECT_EQ(n2.getAction(), "action");
    EXPECT_EQ(n3.getAction(), "action");
    EXPECT_EQ(n4.getAction(), "action");
    EXPECT_EQ(n5.getAction(), "action");
    EXPECT_EQ(n6.getAction(), "action");
    EXPECT_EQ(n7.getAction(), "action");
    EXPECT_EQ(n8.getAction(), "--rubbish");
    EXPECT_EQ(n9.getAction(), "action");
    EXPECT_EQ(n10.getAction(), "action");
    EXPECT_EQ(n11.getAction(), "action");
    EXPECT_EQ(n12.getAction(), "action");
    EXPECT_EQ(n13.getAction(), "action");
    EXPECT_EQ(n14.getAction(), "action");
    EXPECT_EQ(n15.getAction(), "action");
    EXPECT_EQ(n16.getAction(), "action");
    EXPECT_EQ(n17.getAction(), "action");
    EXPECT_EQ(n18.getAction(), "action");
    EXPECT_EQ(n19.getAction(), "--rubbish");
    EXPECT_EQ(n20.getAction(), "--rubbish");
    EXPECT_EQ(n21.getAction(), "action");
    EXPECT_EQ(n22.getAction(), "action");
    EXPECT_EQ(n23.getAction(), "action");
    EXPECT_EQ(n24.getAction(), "action");
}

// TEST_F(InputMethods, IsEmpty) {
//    EXPECT_EQ(n0.isEmpty(), true);
//    EXPECT_EQ(n1.isEmpty(), false);
//    EXPECT_EQ(n2.isEmpty(), false);
//    EXPECT_EQ(n3.isEmpty(), false);
//}
//
// TEST_F(InputMethods, HasOption_String) {
//    /* Basic expectations */
//    EXPECT_EQ(n0.hasOption("first argument"), false);
//    EXPECT_EQ(n1.hasOption("first argument"), false);
//    EXPECT_EQ(n2.hasOption("first argument"), true);
//    EXPECT_EQ(n3.hasOption("first argument"), true);
//    EXPECT_EQ(n3.hasOption("2nd"), true);
//    EXPECT_EQ(n3.hasOption("action"), true);
//
//    /* Shouldn't match the program name */
//    EXPECT_EQ(n0.hasOption("todo"), false);
//    EXPECT_EQ(n1.hasOption("todo"), false);
//
//    /* Check similar strings and substrings don't match */
//    EXPECT_EQ(n3.hasOption("first arguments"), false);
//    EXPECT_EQ(n3.hasOption("first argument "), false);
//
//    /* Empty string shouldn't match anything */
//    EXPECT_EQ(n3.hasOption(""), false);
//}
//
// TEST_F(InputMethods, HasOption_Index) {
//    /* Basic expectations */
//    EXPECT_EQ(n0.hasOption(0), false);
//    EXPECT_EQ(n0.hasOption(1), false);
//    EXPECT_EQ(n0.hasOption(2), false);
//    EXPECT_EQ(n0.hasOption(3), false);
//    EXPECT_EQ(n3.hasOption(0), true);
//    EXPECT_EQ(n3.hasOption(1), true);
//    EXPECT_EQ(n3.hasOption(2), true);
//    EXPECT_EQ(n3.hasOption(3), false);
//
//    /* Negatives should always return false */
//    EXPECT_EQ(n3.hasOption(-1), false);
//}
//
// TEST_F(InputMethods, HasOption_StringAndIndex) {
//    /* Basic expectations */
//    EXPECT_EQ(n3.hasOption("action", 0), true);
//    EXPECT_EQ(n3.hasOption("first argument", 1), true);
//    EXPECT_EQ(n3.hasOption("2nd", 2), true);
//
//    /* Check a different index doesn't match */
//    EXPECT_EQ(n3.hasOption("first argument", 0), false);
//    EXPECT_EQ(n3.hasOption("first argument", 2), false);
//
//    /* Check similar strings and substrings don't match */
//    EXPECT_EQ(n3.hasOption("first", 1), false);
//    EXPECT_EQ(n3.hasOption("first argument ", 1), false);
//
//    /* Empty string shouldn't match anything */
//    EXPECT_EQ(n0.hasOption("", 0), false);
//    EXPECT_EQ(n1.hasOption("", 0), false);
//
//    /* Negatives should always return false */
//    EXPECT_EQ(n3.hasOption("action", -1), false);
//}
//
// TEST_F(InputMethods, GetOption) {
//    /* Basic expectations */
//    EXPECT_EQ(n3.getOption(0), "action");
//    EXPECT_EQ(n3.getOption(1), "first argument");
//    EXPECT_EQ(n3.getOption(2), "2nd");
//
//    /* Invalid indexes should throw exceptions */
//    EXPECT_ANY_THROW(n3.getOption(-1));
//    EXPECT_ANY_THROW(n3.getOption(3));
//}
//
// TEST_F(InputMethods, ToString) {
//    /* Basic expectations */
//    EXPECT_EQ(n0.toString(0), "");
//    EXPECT_EQ(n1.toString(0), "action");
//    EXPECT_EQ(n2.toString(0), "action first argument");
//    EXPECT_EQ(n3.toString(0), "action first argument 2nd");
//    EXPECT_EQ(n3.toString(1), "first argument 2nd");
//    EXPECT_EQ(n3.toString(2), "2nd");
//
//    /* Indexes bigger than size should return an empty string */
//    EXPECT_EQ(n3.toString(3), "");
//    EXPECT_EQ(n3.toString(4), "");
//
//    /* Negative indexes should throw exceptions */
//    EXPECT_ANY_THROW(n3.toString(-1));
//}

/* Construction exceptions */
TEST(InputConstruction, NullArray) {
    EXPECT_THROW(input::Input(0, NULL), std::logic_error);
}

TEST(InputConstruction, EmptyArray) {
    char const *argv[0] = {};
    EXPECT_THROW(input::Input(0, argv), std::logic_error);
}

TEST(InputConstruction, InvalidArgc) {
    char const *argv[0] = {};
    EXPECT_THROW(input::Input(-1, argv), std::logic_error);
}
