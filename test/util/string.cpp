#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "util/string.hpp"

TEST(StringUtils, DemerauLevenshteinDistance) {
    EXPECT_EQ(util::string::demerau_levenshtein_distance("", ""), 0);
    EXPECT_EQ(util::string::demerau_levenshtein_distance(" ", ""), 1);
    EXPECT_EQ(util::string::demerau_levenshtein_distance("", " "), 1);
    EXPECT_EQ(util::string::demerau_levenshtein_distance("test", ""), 4);
    EXPECT_EQ(util::string::demerau_levenshtein_distance("test", "test"), 0);
    EXPECT_EQ(util::string::demerau_levenshtein_distance("test", "tset"), 1);
    EXPECT_EQ(util::string::demerau_levenshtein_distance("test", "tests"), 1);
    EXPECT_EQ(util::string::demerau_levenshtein_distance("test", "est"), 1);
    EXPECT_EQ(util::string::demerau_levenshtein_distance("test", "text"), 1);
    EXPECT_EQ(util::string::demerau_levenshtein_distance("test", "toast"), 2);
    EXPECT_EQ(util::string::demerau_levenshtein_distance("test", "tots"), 2);
    EXPECT_EQ(util::string::demerau_levenshtein_distance("test", "rubbish"), 6);
}

TEST(StringUtils, Corrections) {
    std::vector<std::string> dictionary = {
        "toast", "", "test", "test", "roast", "float", "text",
    };
    EXPECT_EQ(util::string::corrections("", dictionary).size(), 0);
    EXPECT_EQ(util::string::corrections("test", dictionary).size(), 0);
    EXPECT_THAT(util::string::corrections("melt", dictionary),
                testing::ElementsAre("test", "text"));
    EXPECT_THAT(util::string::corrections("next", dictionary),
                testing::ElementsAre("text", "test"));
    EXPECT_THAT(util::string::corrections("bloat", dictionary),
                testing::ElementsAre("float"));
    EXPECT_THAT(util::string::corrections("tast", dictionary),
                testing::ElementsAre("test", "toast", "roast", "text"));
    EXPECT_THAT(util::string::corrections("tast", dictionary, 3),
                testing::ElementsAre("test", "toast", "roast", "text"));
    EXPECT_THAT(
        util::string::corrections("tast", dictionary, 4),
        testing::ElementsAre("test", "toast", "roast", "text", "float"));
}

TEST(StringUtils, LTrim) {
    EXPECT_EQ(util::string::ltrim_copy(""), "");
    EXPECT_EQ(util::string::ltrim_copy(" "), "");
    EXPECT_EQ(util::string::ltrim_copy("   "), "");
    EXPECT_EQ(util::string::ltrim_copy("t"), "t");
    EXPECT_EQ(util::string::ltrim_copy("test"), "test");
    EXPECT_EQ(util::string::ltrim_copy(" test"), "test");
    EXPECT_EQ(util::string::ltrim_copy("test "), "test ");
    EXPECT_EQ(util::string::ltrim_copy(" test "), "test ");
    EXPECT_EQ(util::string::ltrim_copy("   test   "), "test   ");
}

TEST(StringUtils, RTrim) {
    EXPECT_EQ(util::string::rtrim_copy(""), "");
    EXPECT_EQ(util::string::rtrim_copy(" "), "");
    EXPECT_EQ(util::string::rtrim_copy("   "), "");
    EXPECT_EQ(util::string::rtrim_copy("t"), "t");
    EXPECT_EQ(util::string::rtrim_copy("test"), "test");
    EXPECT_EQ(util::string::rtrim_copy(" test"), " test");
    EXPECT_EQ(util::string::rtrim_copy("test "), "test");
    EXPECT_EQ(util::string::rtrim_copy(" test "), " test");
    EXPECT_EQ(util::string::rtrim_copy("   test   "), "   test");
}

TEST(StringUtils, Trim) {
    EXPECT_EQ(util::string::trim_copy(""), "");
    EXPECT_EQ(util::string::trim_copy(" "), "");
    EXPECT_EQ(util::string::trim_copy("   "), "");
    EXPECT_EQ(util::string::trim_copy("t"), "t");
    EXPECT_EQ(util::string::trim_copy("test"), "test");
    EXPECT_EQ(util::string::trim_copy(" test"), "test");
    EXPECT_EQ(util::string::trim_copy("test "), "test");
    EXPECT_EQ(util::string::trim_copy(" test "), "test");
    EXPECT_EQ(util::string::trim_copy("   test   "), "test");
}

TEST(StringUtils, ToInt) {
    EXPECT_EQ(util::string::toint("3"), 3);

    EXPECT_ANY_THROW(util::string::toint(""));

    EXPECT_ANY_THROW(util::string::toint("f"));

    EXPECT_ANY_THROW(util::string::toint("3f"));

    EXPECT_ANY_THROW(util::string::toint("f3"));

    EXPECT_ANY_THROW(util::string::toint("3f3"));
}

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

    EXPECT_EQ(util::string::wrap("longest", 6), "longest");

    EXPECT_EQ(util::string::wrap("longest longest", 6), "longest\nlongest");

    EXPECT_EQ(util::string::wrap("longest longest longest", 6),
              "longest\nlongest\nlongest");

    EXPECT_EQ(util::string::wrap("longest longest", 7), "longest\nlongest");

    EXPECT_EQ(util::string::wrap("longest longest", 8), "longest\nlongest");

    EXPECT_EQ(util::string::wrap("now a short string", 6),
              "now a\nshort\nstring");

    EXPECT_EQ(util::string::wrap("these strings are a problem", 6),
              "these\nstrings\nare a\nproblem");

    EXPECT_EQ(util::string::wrap("what\nif a newline is\nin the mix", 6),
              "what\nif a\nnewline\nis\nin the\nmix");

    EXPECT_EQ(util::string::wrap("", 6, 1), "");

    EXPECT_EQ(util::string::wrap("test", 6, 1), "test");

    EXPECT_EQ(util::string::wrap("longest", 6, 1), "longest");

    EXPECT_EQ(util::string::wrap("longest longest", 6, 1), "longest\n longest");

    EXPECT_EQ(util::string::wrap("now a short string", 6, 1),
              "now a\n short\n string");

    EXPECT_EQ(util::string::wrap("these strings are a problem", 6, 1),
              "these\n strings\n are a\n problem");

    EXPECT_EQ(util::string::wrap("these strings are a problem", 6, 2),
              "these\n  strings\n  are\n  a\n  problem");

    EXPECT_EQ(util::string::wrap("what\nif a newline is\nin the mix", 6, 1),
              "what\n if a\n newline\n is\n in\n the\n mix");

    EXPECT_EQ(util::string::wrap("what\nif a newline is\nin the mix", 6, 2),
              "what\n  if a\n  newline\n  is\n  in\n  the\n  mix");

    EXPECT_EQ(util::string::wrap("what\nif a newline is\nin the mix", 6, 3),
              "what\n   if\n   a\n   newline\n   is\n   in\n   the\n   mix");

    EXPECT_EQ(util::string::wrap("space on edge", 13), "space on edge");

    EXPECT_EQ(util::string::wrap("space on edge of line", 13),
              "space on edge\nof line");

    EXPECT_EQ(util::string::wrap("space on edge", 12), "space on\nedge");

    EXPECT_EQ(util::string::wrap("space on edge of line", 12),
              "space on\nedge of line");

    EXPECT_EQ(util::string::wrap("space on edge", 13, 1), "space on edge");

    EXPECT_EQ(util::string::wrap("space on edge of line test", 13, 1),
              "space on edge\n of line test");

    EXPECT_EQ(util::string::wrap("space on edge", 12, 1), "space on\n edge");

    EXPECT_EQ(util::string::wrap("space on edge of line", 12, 1),
              "space on\n edge of\n line");

    EXPECT_EQ(util::string::wrap("space on edge of line test", 13, 2),
              "space on edge\n  of line\n  test");

    EXPECT_EQ(util::string::wrap("space on edge of line", 12, 2),
              "space on\n  edge of\n  line");

    EXPECT_EQ(util::string::wrap("space on edge of line", 12, 11),
              "space on\n           edge\n           of\n           line");

    EXPECT_EQ(util::string::wrap("   what about leading whitespace?", 13, 2),
              "   what about\n  leading\n  whitespace?");
}
