#include "gtest/gtest.h"

#include "task/type.hpp"
#include "util/string.hpp"

/* Construction exceptions */
TEST(Type, Construction) {
    todo::task::Type urgentName = todo::task::Type("urgent");
    todo::task::Type urgentPure = todo::task::Type(todo::task::Type::urgent);

    EXPECT_EQ(urgentName, todo::task::Type::urgent);
    EXPECT_EQ(urgentPure, todo::task::Type::urgent);

    todo::task::Type lowName = todo::task::Type("low");
    todo::task::Type lowPure = todo::task::Type(todo::task::Type::low);

    EXPECT_EQ(lowName, todo::task::Type::low);
    EXPECT_EQ(lowPure, todo::task::Type::low);

    todo::task::Type highName = todo::task::Type("high");
    todo::task::Type highPure = todo::task::Type(todo::task::Type::high);

    EXPECT_EQ(highName, todo::task::Type::high);
    EXPECT_EQ(highPure, todo::task::Type::high);

    todo::task::Type unknwonName = todo::task::Type("rubbish");
    todo::task::Type unknownPure =
        todo::task::Type(todo::task::Type::UNKNOWN_TYPE);

    EXPECT_EQ(unknwonName, todo::task::Type::UNKNOWN_TYPE);
    EXPECT_EQ(unknownPure, todo::task::Type::UNKNOWN_TYPE);
}

/* Check the logical consistency of the Task Type enum */
TEST(Type, LogicalConsistency) {
    std::vector<std::string> names;

    for (todo::task::Type const o : todo::task::Type::ALL_TYPES) {
        auto name = o.to_string();

        /* Only allow alpha-numeric types */
        if (std::find_if_not(name.begin(), name.end(), isalnum) != name.end()) {
            FAIL() << "Task Type '" + name +
                          "' contains a non-alphanumeric character";
        }

        /* Don't allow the same type name but with different cases */
        auto nameUpper = util::string::toupper(name);
        auto i = std::find_if(
            names.begin(), names.end(), [nameUpper](std::string n) {
                return (util::string::toupper(n) == nameUpper);
            });
        if (i != names.end()) {
            FAIL() << "Task Type '" + name +
                          "' conflicts with other declared types '" + *i + "'";
        } else {
            names.push_back(name);
        }
    }
}

/* Test the isValid functionality */
TEST(Type, IsValid) {
    EXPECT_TRUE(todo::task::Type::is_valid("urgent"));
    EXPECT_TRUE(todo::task::Type::is_valid("done"));
    EXPECT_TRUE(todo::task::Type::is_valid("normal"));
    EXPECT_FALSE(todo::task::Type::is_valid("rubbish"));
    EXPECT_FALSE(todo::task::Type::is_valid(""));
    EXPECT_FALSE(todo::task::Type::is_valid("urgentt"));
    EXPECT_FALSE(todo::task::Type::is_valid("urgent "));
}

/* Test the to_string functionality */
TEST(Type, ToString) {
    todo::task::Type urgent = todo::task::Type::urgent;
    EXPECT_EQ(urgent.to_string(), "urgent");

    todo::task::Type done = todo::task::Type::done;
    EXPECT_EQ(done.to_string(), "done");

    todo::task::Type normal = todo::task::Type::normal;
    EXPECT_EQ(normal.to_string(), "normal");

    todo::task::Type unknown = todo::task::Type::UNKNOWN_TYPE;
    EXPECT_EQ(unknown.to_string(), "");

    todo::task::Type rubbish = todo::task::Type("rubbish");
    EXPECT_EQ(rubbish.to_string(), "");
}

/* Test the character representation functionality */
TEST(Type, CharacterRepresentation) {
    todo::task::Type urgent = todo::task::Type::urgent;
    EXPECT_EQ(urgent.get_char_representation(), '!');

    todo::task::Type high = todo::task::Type::high;
    EXPECT_EQ(high.get_char_representation(), '!');

    todo::task::Type done = todo::task::Type::done;
    EXPECT_EQ(done.get_char_representation(), '+');

    todo::task::Type normal = todo::task::Type::normal;
    EXPECT_EQ(normal.get_char_representation(), '-');

    todo::task::Type unknown = todo::task::Type::UNKNOWN_TYPE;
    EXPECT_EQ(unknown.get_char_representation(), todo::task::Type::NULL_CHAR);
}
