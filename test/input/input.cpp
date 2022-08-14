#include "gtest/gtest.h"

#include "input/input.hpp"
#include "input/option.hpp"

/* Fixture class to test each public method */
class InputMethods : public ::testing::Test {
  public:
    InputMethods()
        : n0(1, a0), n1(2, a1), n2(3, a2), n3(4, a3), n4(5, a4), n5(5, a5),
          n6(5, a6), n7(6, a7), n8(6, a8), n9(6, a9), n10(6, a10), n11(6, a11),
          n12(6, a12), n13(6, a13), n14(6, a14), n15(6, a15) {}

  protected:
    char const *a0[1] = {"todo"};
    char const *a1[2] = {"todo", "action"};
    char const *a2[3] = {"todo", "action", "first argument"};
    char const *a3[4] = {"todo", "action", "first argument", "2nd"};
    char const *a4[5] = {"todo", "action", "--global", "first argument", "2nd"};
    char const *a5[5] = {"todo", "action", "first argument", "--global", "2nd"};
    char const *a6[5] = {"todo", "--global", "action", "first argument", "2nd"};
    char const *a7[6] = {"todo",  "action",         "--global",
                         "--all", "first argument", "2nd"};
    char const *a8[6] = {"todo",           "action", "--global",
                         "first argument", "--all",  "2nd"};
    char const *a9[6] = {"todo",  "--global",       "action",
                         "--all", "first argument", "2nd"};
    char const *a10[6] = {"todo",           "--global", "action",
                          "first argument", "--all",    "2nd"};
    char const *a11[6] = {"todo",     "action",         "--",
                          "--global", "first argument", "2nd"};
    char const *a12[6] = {"todo", "action",   "first argument",
                          "--",   "--global", "2nd"};
    char const *a13[6] = {"todo",           "--", "action", "--global",
                          "first argument", "2nd"};
    char const *a14[6] = {"todo",           "--", "--global", "action",
                          "first argument", "2nd"};
    char const *a15[6] = {"todo", "action", "--global",
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
};

/* Test all public methods */
TEST_F(InputMethods, GetAction) {
    EXPECT_EQ(n0.get_action(), "");
    EXPECT_EQ(n1.get_action(), "action");
    EXPECT_EQ(n2.get_action(), "action");
    EXPECT_EQ(n3.get_action(), "action");
    EXPECT_EQ(n4.get_action(), "action");
    EXPECT_EQ(n5.get_action(), "action");
    EXPECT_EQ(n6.get_action(), "action");
    EXPECT_EQ(n7.get_action(), "action");
    EXPECT_EQ(n8.get_action(), "action");
    EXPECT_EQ(n9.get_action(), "action");
    EXPECT_EQ(n10.get_action(), "action");
    EXPECT_EQ(n11.get_action(), "action");
    EXPECT_EQ(n12.get_action(), "action");
    EXPECT_EQ(n13.get_action(), "action");
    EXPECT_EQ(n14.get_action(), "--global");
}

TEST_F(InputMethods, GetActionArgCount) {
    EXPECT_EQ(n0.get_action_arg_count(), 0);
    EXPECT_EQ(n1.get_action_arg_count(), 0);
    EXPECT_EQ(n2.get_action_arg_count(), 1);
    EXPECT_EQ(n3.get_action_arg_count(), 2);
    EXPECT_EQ(n4.get_action_arg_count(), 2);
    EXPECT_EQ(n5.get_action_arg_count(), 2);
    EXPECT_EQ(n6.get_action_arg_count(), 2);
    EXPECT_EQ(n7.get_action_arg_count(), 2);
    EXPECT_EQ(n8.get_action_arg_count(), 2);
    EXPECT_EQ(n9.get_action_arg_count(), 2);
    EXPECT_EQ(n10.get_action_arg_count(), 2);
    EXPECT_EQ(n11.get_action_arg_count(), 3);
    EXPECT_EQ(n12.get_action_arg_count(), 3);
    EXPECT_EQ(n13.get_action_arg_count(), 3);
    EXPECT_EQ(n14.get_action_arg_count(), 3);
    EXPECT_EQ(n15.get_action_arg_count(), 2);
}

TEST_F(InputMethods, GetActionArg) {
    /* Basic expectations */
    EXPECT_EQ(n3.get_action_arg(0), "first argument");
    EXPECT_EQ(n3.get_action_arg(1), "2nd");

    /* Options should be ignored */
    EXPECT_EQ(n4.get_action_arg(0), "first argument");
    EXPECT_EQ(n4.get_action_arg(1), "2nd");
    EXPECT_EQ(n5.get_action_arg(0), "first argument");
    EXPECT_EQ(n5.get_action_arg(1), "2nd");
    EXPECT_EQ(n6.get_action_arg(0), "first argument");
    EXPECT_EQ(n6.get_action_arg(1), "2nd");
    EXPECT_EQ(n7.get_action_arg(0), "first argument");
    EXPECT_EQ(n7.get_action_arg(1), "2nd");
    EXPECT_EQ(n8.get_action_arg(0), "first argument");
    EXPECT_EQ(n8.get_action_arg(1), "2nd");
    EXPECT_EQ(n9.get_action_arg(0), "first argument");
    EXPECT_EQ(n9.get_action_arg(1), "2nd");
    EXPECT_EQ(n10.get_action_arg(0), "first argument");
    EXPECT_EQ(n10.get_action_arg(1), "2nd");
    EXPECT_EQ(n11.get_action_arg(0), "--global");
    EXPECT_EQ(n11.get_action_arg(1), "first argument");
    EXPECT_EQ(n11.get_action_arg(2), "2nd");
    EXPECT_EQ(n12.get_action_arg(0), "first argument");
    EXPECT_EQ(n12.get_action_arg(1), "--global");
    EXPECT_EQ(n12.get_action_arg(2), "2nd");
    EXPECT_EQ(n13.get_action_arg(0), "--global");
    EXPECT_EQ(n13.get_action_arg(1), "first argument");
    EXPECT_EQ(n13.get_action_arg(2), "2nd");
    EXPECT_EQ(n14.get_action_arg(0), "action");
    EXPECT_EQ(n14.get_action_arg(1), "first argument");
    EXPECT_EQ(n14.get_action_arg(2), "2nd");
    EXPECT_EQ(n15.get_action_arg(0), "--all");
    EXPECT_EQ(n15.get_action_arg(1), "first argument");

    /* Invalid indexes should throw exceptions */
    EXPECT_ANY_THROW(n3.get_action_arg(-1));
    EXPECT_ANY_THROW(n3.get_action_arg(2));
}

TEST_F(InputMethods, GetActionArgString) {
    /* Basic expectations */
    EXPECT_EQ(n0.get_action_arg_string(), "");
    EXPECT_EQ(n1.get_action_arg_string(), "");
    EXPECT_EQ(n2.get_action_arg_string(), "first argument");
    EXPECT_EQ(n3.get_action_arg_string(), "first argument 2nd");
    EXPECT_EQ(n3.get_action_arg_string(0), "first argument 2nd");
    EXPECT_EQ(n3.get_action_arg_string(1), "2nd");
    EXPECT_EQ(n4.get_action_arg_string(), "first argument 2nd");
    EXPECT_EQ(n5.get_action_arg_string(), "first argument 2nd");
    EXPECT_EQ(n6.get_action_arg_string(), "first argument 2nd");
    EXPECT_EQ(n7.get_action_arg_string(), "first argument 2nd");
    EXPECT_EQ(n8.get_action_arg_string(), "first argument 2nd");
    EXPECT_EQ(n9.get_action_arg_string(), "first argument 2nd");
    EXPECT_EQ(n10.get_action_arg_string(), "first argument 2nd");
    EXPECT_EQ(n11.get_action_arg_string(), "--global first argument 2nd");
    EXPECT_EQ(n12.get_action_arg_string(), "first argument --global 2nd");
    EXPECT_EQ(n13.get_action_arg_string(), "--global first argument 2nd");
    EXPECT_EQ(n14.get_action_arg_string(), "action first argument 2nd");
    EXPECT_EQ(n15.get_action_arg_string(), "--all first argument");

    /* Indexes bigger than size should return an empty string */
    EXPECT_EQ(n3.get_action_arg_string(2), "");
    EXPECT_EQ(n3.get_action_arg_string(3), "");

    /* Negative indexes should throw exceptions */
    EXPECT_ANY_THROW(n3.get_action_arg_string(-1));
}

TEST_F(InputMethods, HasActionArg_Index) {
    /* Basic expectations */
    EXPECT_EQ(n0.has_action_arg(0), false);
    EXPECT_EQ(n0.has_action_arg(1), false);
    EXPECT_EQ(n0.has_action_arg(2), false);
    EXPECT_EQ(n0.has_action_arg(3), false);
    EXPECT_EQ(n3.has_action_arg(0), true);
    EXPECT_EQ(n3.has_action_arg(1), true);
    EXPECT_EQ(n3.has_action_arg(2), false);
    EXPECT_EQ(n3.has_action_arg(3), false);

    /* Negatives should always return false */
    EXPECT_EQ(n3.has_action_arg(-1), false);
}

TEST_F(InputMethods, HasActionArg_String) {
    /* Basic expectations */
    EXPECT_EQ(n0.has_action_arg("first argument"), false);
    EXPECT_EQ(n1.has_action_arg("first argument"), false);
    EXPECT_EQ(n2.has_action_arg("first argument"), true);
    EXPECT_EQ(n3.has_action_arg("action"), false);
    EXPECT_EQ(n3.has_action_arg("first argument"), true);
    EXPECT_EQ(n3.has_action_arg("2nd"), true);

    /* Shouldn't match the program name */
    EXPECT_EQ(n0.has_action_arg("todo"), false);
    EXPECT_EQ(n1.has_action_arg("todo"), false);

    /* Check similar strings and substrings don't match */
    EXPECT_EQ(n3.has_action_arg("first arguments"), false);
    EXPECT_EQ(n3.has_action_arg("first argument "), false);

    /* Empty string shouldn't match anything */
    EXPECT_EQ(n3.has_action_arg(""), false);
}

TEST_F(InputMethods, HasActionArg_StringAndIndex) {
    /* Basic expectations */
    EXPECT_EQ(n12.has_action_arg("first argument", 0), true);
    EXPECT_EQ(n12.has_action_arg("--global", 1), true);
    EXPECT_EQ(n12.has_action_arg("2nd", 2), true);

    /* Check a different index doesn't match */
    EXPECT_EQ(n12.has_action_arg("--", 0), false);
    EXPECT_EQ(n12.has_action_arg("--", 1), false);
    EXPECT_EQ(n12.has_action_arg("--", 2), false);
    EXPECT_EQ(n12.has_action_arg("2nd", 0), false);
    EXPECT_EQ(n12.has_action_arg("2nd", 1), false);

    /* Check similar strings and substrings don't match */
    EXPECT_EQ(n12.has_action_arg("first", 0), false);
    EXPECT_EQ(n12.has_action_arg("first argument ", 0), false);

    /* Empty string shouldn't match anything */
    EXPECT_EQ(n0.has_action_arg("", 0), false);
    EXPECT_EQ(n1.has_action_arg("", 0), false);

    /* Negatives should always return false */
    EXPECT_EQ(n3.has_action_arg("action", -1), false);
}

TEST_F(InputMethods, HasOption) {
    EXPECT_EQ(n0.has_option(input::Option::global), false);
    EXPECT_EQ(n1.has_option(input::Option::global), false);
    EXPECT_EQ(n2.has_option(input::Option::global), false);
    EXPECT_EQ(n3.has_option(input::Option::global), false);
    EXPECT_EQ(n4.has_option(input::Option::global), true);
    EXPECT_EQ(n5.has_option(input::Option::global), true);
    EXPECT_EQ(n6.has_option(input::Option::global), true);
    EXPECT_EQ(n7.has_option(input::Option::global), true);
    EXPECT_EQ(n7.has_option(input::Option::all), true);
    EXPECT_EQ(n8.has_option(input::Option::global), true);
    EXPECT_EQ(n8.has_option(input::Option::all), true);
    EXPECT_EQ(n9.has_option(input::Option::global), true);
    EXPECT_EQ(n9.has_option(input::Option::all), true);
    EXPECT_EQ(n10.has_option(input::Option::global), true);
    EXPECT_EQ(n10.has_option(input::Option::all), true);
    EXPECT_EQ(n11.has_option(input::Option::global), false);
    EXPECT_EQ(n12.has_option(input::Option::global), false);
    EXPECT_EQ(n13.has_option(input::Option::global), false);
    EXPECT_EQ(n14.has_option(input::Option::global), false);
    EXPECT_EQ(n15.has_option(input::Option::global), true);
    EXPECT_EQ(n15.has_option(input::Option::all), false);
}

TEST_F(InputMethods, GetOptionArgs) {
    EXPECT_EQ(n0.get_option_args(input::Option::global).size(), 0);
    EXPECT_EQ(n4.get_option_args(input::Option::global).size(), 0);
    EXPECT_EQ(n7.get_option_args(input::Option::global).size(), 0);
    EXPECT_EQ(n7.get_option_args(input::Option::all).size(), 0);
    EXPECT_EQ(n7.get_option_args(input::Option::UNKNOWN_OPTION).size(), 0);
}

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

TEST(InputConstruction, UnknownOption) {
    char const *argv[5] = {"todo", "action", "--rubbish", "first argument",
                           "2nd"};
    EXPECT_THROW(input::Input(5, argv), std::runtime_error);
}
