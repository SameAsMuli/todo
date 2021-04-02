#include <algorithm> // std::find, std::find_if_not
#include <string>    // std::string
#include <vector>    // std::vector

#include "input/option_type.hpp"
#include "util/string.hpp"

#include "gtest/gtest.h"

/* Construction exceptions */
TEST(OptionType, Construction) {
    input::OptionType allLong = input::OptionType("all");
    input::OptionType allPure = input::OptionType(input::OptionType::all);
    input::OptionType allShort = input::OptionType("a");

    EXPECT_EQ(allLong, input::OptionType::all);
    EXPECT_EQ(allPure, input::OptionType::all);
    EXPECT_EQ(allShort, input::OptionType::all);

    input::OptionType globalLong = input::OptionType("global");
    input::OptionType globalPure = input::OptionType(input::OptionType::global);
    input::OptionType globalShort = input::OptionType('g');

    EXPECT_EQ(globalLong, input::OptionType::global);
    EXPECT_EQ(globalPure, input::OptionType::global);
    EXPECT_EQ(globalShort, input::OptionType::global);

    input::OptionType localLong = input::OptionType("local");
    input::OptionType localPure = input::OptionType(input::OptionType::local);
    input::OptionType localShort = input::OptionType("l");

    EXPECT_EQ(localLong, input::OptionType::local);
    EXPECT_EQ(localPure, input::OptionType::local);
    EXPECT_EQ(localShort, input::OptionType::local);

    input::OptionType unknownLong = input::OptionType("rubbish");
    input::OptionType unknownPure =
        input::OptionType(input::OptionType::UNKNOWN_OPTION_TYPE);
    input::OptionType unknownShort = input::OptionType("R");

    EXPECT_EQ(unknownLong, input::OptionType::UNKNOWN_OPTION_TYPE);
    EXPECT_EQ(unknownPure, input::OptionType::UNKNOWN_OPTION_TYPE);
    EXPECT_EQ(unknownShort, input::OptionType::UNKNOWN_OPTION_TYPE);
}

/* Check the logical consistency of the Option Type enum */
TEST(OptionType, LogicalConsistency) {
    std::vector<std::string> names;

    for (input::OptionType const o : input::OptionType::ALL_TYPES) {
        auto name = o.toString();

        /* Strip the prefix */
        name.erase(0, input::OptionType::LONG_OPTION_PREFIX.size());

        /* Only allow alpha-numeric option types */
        if (std::find_if_not(name.begin(), name.end(), isalnum) != name.end()) {
            FAIL() << "Option Type '" + name +
                          "' contains a non-alphanumeric character";
        }

        /* Don't allow the same option type but with different cases */
        auto nameUpper = util::string::toupper(name);
        auto i = std::find_if(
            names.begin(), names.end(), [nameUpper](std::string n) {
                return (util::string::toupper(n) == nameUpper);
            });
        if (i != names.end()) {
            FAIL() << "Option Type '" + name +
                          "' conflicts with other declared option type '" + *i +
                          "'";
        } else {
            names.push_back(name);
        }
    }
}

/* Test the isValid functionality */
TEST(OptionType, IsValid) {
    EXPECT_TRUE(input::OptionType::isValid("all"));
    EXPECT_TRUE(input::OptionType::isValid("global"));
    EXPECT_TRUE(input::OptionType::isValid("local"));
    EXPECT_TRUE(input::OptionType::isValid("a"));
    EXPECT_TRUE(input::OptionType::isValid("g"));
    EXPECT_TRUE(input::OptionType::isValid("l"));
    EXPECT_FALSE(input::OptionType::isValid("rubbish"));
    EXPECT_FALSE(input::OptionType::isValid("R"));
    EXPECT_FALSE(input::OptionType::isValid(""));
    EXPECT_FALSE(input::OptionType::isValid("alll"));
    EXPECT_FALSE(input::OptionType::isValid("all "));
}

/* Test the toString functionality */
TEST(OptionType, ToString) {
    input::OptionType all = input::OptionType::all;
    EXPECT_EQ(all.toString(), "--all");

    input::OptionType allShort = input::OptionType("a");
    EXPECT_EQ(allShort.toString(), "-a");

    input::OptionType global = input::OptionType::global;
    EXPECT_EQ(global.toString(), "--global");

    input::OptionType globalShort = input::OptionType("g");
    EXPECT_EQ(globalShort.toString(), "-g");

    input::OptionType local = input::OptionType::local;
    EXPECT_EQ(local.toString(), "--local");

    input::OptionType localShort = input::OptionType("l");
    EXPECT_EQ(localShort.toString(), "-l");

    input::OptionType unknown = input::OptionType::UNKNOWN_OPTION_TYPE;
    EXPECT_EQ(unknown.toString(), "");

    input::OptionType rubbish = input::OptionType("rubbish");
    EXPECT_EQ(rubbish.toString(), "");
}

/* Test the parameter count functionality */
TEST(OptionType, ParamCount) {
    input::OptionType all = input::OptionType::all;
    EXPECT_EQ(all.getParamCount(), 0);

    input::OptionType global = input::OptionType::global;
    EXPECT_EQ(global.getParamCount(), 0);

    input::OptionType local = input::OptionType::local;
    EXPECT_EQ(local.getParamCount(), 0);

    input::OptionType unknown = input::OptionType::UNKNOWN_OPTION_TYPE;
    EXPECT_EQ(unknown.getParamCount(), 0);
}

/* Test the character representation functionality */
TEST(OptionType, CharacterRepresentation) {
    input::OptionType all = input::OptionType::all;
    EXPECT_TRUE(all.hasCharRepresentation());
    EXPECT_EQ(all.getCharRepresentation(), 'a');

    input::OptionType global = input::OptionType::global;
    EXPECT_TRUE(global.hasCharRepresentation());
    EXPECT_EQ(global.getCharRepresentation(), 'g');

    input::OptionType local = input::OptionType::local;
    EXPECT_TRUE(local.hasCharRepresentation());
    EXPECT_EQ(local.getCharRepresentation(), 'l');

    input::OptionType unknown = input::OptionType::UNKNOWN_OPTION_TYPE;
    EXPECT_FALSE(unknown.hasCharRepresentation());
    EXPECT_EQ(unknown.getCharRepresentation(), input::OptionType::NULL_CHAR);
}
