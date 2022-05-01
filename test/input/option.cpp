#include <algorithm> // std::find, std::find_if_not
#include <string>    // std::string
#include <vector>    // std::vector

#include "input/option.hpp"
#include "util/string.hpp"

#include "gtest/gtest.h"

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
        auto name = o.toString();

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
    EXPECT_TRUE(input::Option::isValid("all"));
    EXPECT_TRUE(input::Option::isValid("global"));
    EXPECT_TRUE(input::Option::isValid("local"));
    EXPECT_TRUE(input::Option::isValid("a"));
    EXPECT_TRUE(input::Option::isValid("g"));
    EXPECT_TRUE(input::Option::isValid("l"));
    EXPECT_FALSE(input::Option::isValid("rubbish"));
    EXPECT_FALSE(input::Option::isValid("R"));
    EXPECT_FALSE(input::Option::isValid(""));
    EXPECT_FALSE(input::Option::isValid("alll"));
    EXPECT_FALSE(input::Option::isValid("all "));
}

/* Test the toString functionality */
TEST(Option, ToString) {
    input::Option all = input::Option::all;
    EXPECT_EQ(all.toString(), "--all");

    input::Option allShort = input::Option("a");
    EXPECT_EQ(allShort.toString(), "-a");

    input::Option global = input::Option::global;
    EXPECT_EQ(global.toString(), "--global");

    input::Option globalShort = input::Option("g");
    EXPECT_EQ(globalShort.toString(), "-g");

    input::Option local = input::Option::local;
    EXPECT_EQ(local.toString(), "--local");

    input::Option localShort = input::Option("l");
    EXPECT_EQ(localShort.toString(), "-l");

    input::Option unknown = input::Option::UNKNOWN_OPTION;
    EXPECT_EQ(unknown.toString(), "");

    input::Option rubbish = input::Option("rubbish");
    EXPECT_EQ(rubbish.toString(), "");
}

/* Test the parameter count functionality */
TEST(Option, RequiresArg) {
    input::Option all = input::Option::all;
    EXPECT_EQ(all.requiresArg(), false);

    input::Option local = input::Option::local;
    EXPECT_EQ(local.requiresArg(), false);

    input::Option unknown = input::Option::UNKNOWN_OPTION;
    EXPECT_EQ(unknown.requiresArg(), false);
}

/* Test the character representation functionality */
TEST(Option, CharacterRepresentation) {
    input::Option all = input::Option::all;
    EXPECT_TRUE(all.hasCharRepresentation());
    EXPECT_EQ(all.getCharRepresentation(), 'a');

    input::Option global = input::Option::global;
    EXPECT_TRUE(global.hasCharRepresentation());
    EXPECT_EQ(global.getCharRepresentation(), 'g');

    input::Option local = input::Option::local;
    EXPECT_TRUE(local.hasCharRepresentation());
    EXPECT_EQ(local.getCharRepresentation(), 'l');

    input::Option unknown = input::Option::UNKNOWN_OPTION;
    EXPECT_FALSE(unknown.hasCharRepresentation());
    EXPECT_EQ(unknown.getCharRepresentation(), input::Option::NULL_CHAR);
}
