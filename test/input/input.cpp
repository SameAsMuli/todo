#include "input/input.hpp"
#include "gtest/gtest.h"

/* Fixture class to test each public method */
class InputMethod : public ::testing::Test {
  public:
    InputMethod() : n0(1, a0), n1(2, a1), n2(3, a2), n3(4, a3) {}

  protected:
    char const *a0[1] = {"todo"};
    char const *a1[2] = {"todo", "action"};
    char const *a2[3] = {"todo", "action", "first option"};
    char const *a3[4] = {"todo", "action", "first option", "2nd"};
    input::Input n0;
    input::Input n1;
    input::Input n2;
    input::Input n3;
};

/* Test all public methods */
TEST_F(InputMethod, Size) {
    EXPECT_EQ(n0.size(), 0);
    EXPECT_EQ(n1.size(), 1);
    EXPECT_EQ(n2.size(), 2);
    EXPECT_EQ(n3.size(), 3);
}

TEST_F(InputMethod, IsEmpty) {
    EXPECT_EQ(n0.isEmpty(), true);
    EXPECT_EQ(n1.isEmpty(), false);
    EXPECT_EQ(n2.isEmpty(), false);
    EXPECT_EQ(n3.isEmpty(), false);
}

TEST_F(InputMethod, HasOption_String) {
    /* Basic expectations */
    EXPECT_EQ(n0.hasOption("first option"), false);
    EXPECT_EQ(n1.hasOption("first option"), false);
    EXPECT_EQ(n2.hasOption("first option"), true);
    EXPECT_EQ(n3.hasOption("first option"), true);
    EXPECT_EQ(n3.hasOption("2nd"), true);
    EXPECT_EQ(n3.hasOption("action"), true);

    /* Shouldn't match the program name */
    EXPECT_EQ(n0.hasOption("todo"), false);
    EXPECT_EQ(n1.hasOption("todo"), false);

    /* Check similar strings and substrings don't match */
    EXPECT_EQ(n3.hasOption("first options"), false);
    EXPECT_EQ(n3.hasOption("first option "), false);

    /* Empty string shouldn't match anything */
    EXPECT_EQ(n3.hasOption(""), false);
}

TEST_F(InputMethod, HasOption_Index) {
    /* Basic expectations */
    EXPECT_EQ(n0.hasOption(0), false);
    EXPECT_EQ(n0.hasOption(1), false);
    EXPECT_EQ(n0.hasOption(2), false);
    EXPECT_EQ(n0.hasOption(3), false);
    EXPECT_EQ(n3.hasOption(0), true);
    EXPECT_EQ(n3.hasOption(1), true);
    EXPECT_EQ(n3.hasOption(2), true);
    EXPECT_EQ(n3.hasOption(3), false);

    /* Negatives should always return false */
    EXPECT_EQ(n3.hasOption(-1), false);
}

TEST_F(InputMethod, HasOption_StringAndIndex) {
    /* Basic expectations */
    EXPECT_EQ(n3.hasOption("action", 0), true);
    EXPECT_EQ(n3.hasOption("first option", 1), true);
    EXPECT_EQ(n3.hasOption("2nd", 2), true);

    /* Check a different index doesn't match */
    EXPECT_EQ(n3.hasOption("first option", 0), false);
    EXPECT_EQ(n3.hasOption("first option", 2), false);

    /* Check similar strings and substrings don't match */
    EXPECT_EQ(n3.hasOption("first", 1), false);
    EXPECT_EQ(n3.hasOption("first option ", 1), false);

    /* Empty string shouldn't match anything */
    EXPECT_EQ(n0.hasOption("", 0), false);
    EXPECT_EQ(n1.hasOption("", 0), false);

    /* Negatives should always return false */
    EXPECT_EQ(n3.hasOption("action", -1), false);
}

TEST_F(InputMethod, GetOption) {
    /* Basic expectations */
    EXPECT_EQ(n3.getOption(0), "action");
    EXPECT_EQ(n3.getOption(1), "first option");
    EXPECT_EQ(n3.getOption(2), "2nd");

    /* Invalid indexes should throw exceptions */
    EXPECT_ANY_THROW(n3.getOption(-1));
    EXPECT_ANY_THROW(n3.getOption(3));
}

TEST_F(InputMethod, ToString) {
    /* Basic expectations */
    EXPECT_EQ(n0.toString(0), "");
    EXPECT_EQ(n1.toString(0), "action");
    EXPECT_EQ(n2.toString(0), "action first option");
    EXPECT_EQ(n3.toString(0), "action first option 2nd");
    EXPECT_EQ(n3.toString(1), "first option 2nd");
    EXPECT_EQ(n3.toString(2), "2nd");

    /* Indexes bigger than size should return an empty string */
    EXPECT_EQ(n3.toString(3), "");
    EXPECT_EQ(n3.toString(4), "");

    /* Negative indexes should throw exceptions */
    EXPECT_ANY_THROW(n3.toString(-1));
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
