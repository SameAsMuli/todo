#include "util/string.hpp"
#include "gtest/gtest.h"

TEST(StringUtils, ToUpper) {
    EXPECT_EQ(util::string::toupper(""), "");

    EXPECT_EQ(util::string::toupper("test"), "TEST");

    EXPECT_EQ(util::string::toupper("all lower"), "ALL LOWER");

    EXPECT_EQ(util::string::toupper("ALL UPPER"), "ALL UPPER");

    EXPECT_EQ(util::string::toupper("a MiXTurE Of tHe TWo"),
              "A MIXTURE OF THE TWO");

    EXPECT_EQ(
        util::string::toupper("+ some punctuation! Wow... pretty cool, huh?"),
        "+ SOME PUNCTUATION! WOW... PRETTY COOL, HUH?");
}

TEST(StringUtils, Wrap) {
    EXPECT_EQ(util::string::wrap("", 6), "");

    EXPECT_EQ(util::string::wrap("test", 6), "test");

    EXPECT_EQ(util::string::wrap("now a short string", 6),
              "now a\nshort\nstring");

    EXPECT_EQ(util::string::wrap("these strings are a problem", 6),
              "these\nstrings\nare a\nproblem");
}
