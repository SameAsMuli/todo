#include <algorithm> // std::find, std::find_if_not
#include <string>    // std::string
#include <vector>    // std::vector

#include "gtest/gtest.h"

#include "input/option.hpp"
#include "util/string.hpp"

/* Construction exceptions */
TEST(Option, Construction) {
    input::Option allLong = input::Option("all");
    input::Option allPure = input::Option(input::Option::all);
    input::Option allShort = input::Option("a");

    EXPECT_EQ(allLong, input::Option::all);
    EXPECT_EQ(allPure, input::Option::all);
    EXPECT_EQ(allShort, input::Option::all);

    input::Option globalLong = input::Option("global");
    input::Option globalPure = input::Option(input::Option::global);
    input::Option globalShort = input::Option('g');

    EXPECT_EQ(globalLong, input::Option::global);
    EXPECT_EQ(globalPure, input::Option::global);
    EXPECT_EQ(globalShort, input::Option::global);

    input::Option localLong = input::Option("local");
    input::Option localPure = input::Option(input::Option::local);
    input::Option localShort = input::Option("l");

    EXPECT_EQ(localLong, input::Option::local);
    EXPECT_EQ(localPure, input::Option::local);
    EXPECT_EQ(localShort, input::Option::local);

    input::Option unknownLong = input::Option("rubbish");
    input::Option unknownPure = input::Option(input::Option::UNKNOWN_OPTION);
    input::Option unknownShort = input::Option("R");

    EXPECT_EQ(unknownLong, input::Option::UNKNOWN_OPTION);
    EXPECT_EQ(unknownPure, input::Option::UNKNOWN_OPTION);
    EXPECT_EQ(unknownShort, input::Option::UNKNOWN_OPTION);
}

/* Check the logical consistency of the Option Type enum */
TEST(Option, LogicalConsistency) {
    std::vector<std::string> names;

    for (input::Option const o : input::Option::ALL_OPTIONS) {
        auto name = o.to_string();

        /* Strip the prefix */
        name.erase(0, input::Option::LONG_OPTION_PREFIX.size());

        /* Only allow alpha-numeric options */
        if (std::find_if_not(name.begin(), name.end(), isalnum) != name.end()) {
            FAIL() << "Option Type '" + name +
                          "' contains a non-alphanumeric character";
        }

        /* Don't allow the same option but with different cases */
        auto nameUpper = util::string::toupper(name);
        auto i = std::find_if(
            names.begin(), names.end(), [nameUpper](std::string n) {
                return (util::string::toupper(n) == nameUpper);
            });
        if (i != names.end()) {
            FAIL() << "Option Type '" + name +
                          "' conflicts with other declared option '" + *i + "'";
        } else {
            names.push_back(name);
        }
    }
}

/* Test the isValid functionality */
TEST(Option, IsValid) {
    EXPECT_TRUE(input::Option::is_valid("all"));
    EXPECT_TRUE(input::Option::is_valid("global"));
    EXPECT_TRUE(input::Option::is_valid("local"));
    EXPECT_TRUE(input::Option::is_valid("a"));
    EXPECT_TRUE(input::Option::is_valid("g"));
    EXPECT_TRUE(input::Option::is_valid("l"));
    EXPECT_FALSE(input::Option::is_valid("rubbish"));
    EXPECT_FALSE(input::Option::is_valid("R"));
    EXPECT_FALSE(input::Option::is_valid(""));
    EXPECT_FALSE(input::Option::is_valid("alll"));
    EXPECT_FALSE(input::Option::is_valid("all "));
}

/* Test the to_string functionality */
TEST(Option, ToString) {
    input::Option all = input::Option::all;
    EXPECT_EQ(all.to_string(), "--all");

    input::Option allShort = input::Option("a");
    EXPECT_EQ(allShort.to_string(), "-a");

    input::Option global = input::Option::global;
    EXPECT_EQ(global.to_string(), "--global");

    input::Option globalShort = input::Option("g");
    EXPECT_EQ(globalShort.to_string(), "-g");

    input::Option local = input::Option::local;
    EXPECT_EQ(local.to_string(), "--local");

    input::Option localShort = input::Option("l");
    EXPECT_EQ(localShort.to_string(), "-l");

    input::Option unknown = input::Option::UNKNOWN_OPTION;
    EXPECT_EQ(unknown.to_string(), "");

    input::Option rubbish = input::Option("rubbish");
    EXPECT_EQ(rubbish.to_string(), "");
}

/* Test the parameter count functionality */
TEST(Option, RequiresArg) {
    input::Option all = input::Option::all;
    EXPECT_EQ(all.requires_arg(), false);

    input::Option local = input::Option::local;
    EXPECT_EQ(local.requires_arg(), false);

    input::Option unknown = input::Option::UNKNOWN_OPTION;
    EXPECT_EQ(unknown.requires_arg(), false);
}

/* Test the character representation functionality */
TEST(Option, CharacterRepresentation) {
    input::Option all = input::Option::all;
    EXPECT_TRUE(all.has_char_representation());
    EXPECT_EQ(all.get_char_representation(), 'a');

    input::Option global = input::Option::global;
    EXPECT_TRUE(global.has_char_representation());
    EXPECT_EQ(global.get_char_representation(), 'g');

    input::Option local = input::Option::local;
    EXPECT_TRUE(local.has_char_representation());
    EXPECT_EQ(local.get_char_representation(), 'l');

    input::Option unknown = input::Option::UNKNOWN_OPTION;
    EXPECT_FALSE(unknown.has_char_representation());
    EXPECT_EQ(unknown.get_char_representation(), input::Option::NULL_CHAR);
}
