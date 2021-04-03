#ifndef INPUT_OPTION_TYPE_H
#define INPUT_OPTION_TYPE_H

#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
#include <vector>

namespace input {

/* Define the list of command line option types *nd the number of arguments that
 * can be passed to them. */
#define OPTION_TYPES(F) F(all, 0), F(global, 0), F(help, 0), F(local, 0)

/**
 * @brief A class to describe the available command line options.
 *
 * The class acts as a wrapper around an enum. The enum describes all possible
 * option types for any action, which allows consistency when using the same
 * options across different actions.
 *
 * Every option type has a long name, which is passed to the program in the
 * format:
 *
 *   --longname
 *
 * A type can also be optionally given a single character reference, which is
 * defined in getCharRepresentation and can be passed to the program in the
 * format:
 *
 *   -l
 *
 * Option types can be passed a set number of arguments, specified by the
 * argument count e.g. an option type with an argument count of 2 would be
 * passed to the program as follows:
 *
 *   --longname argument1 argument2
 */
class OptionType {

  public:
#define F(e, n) e
    /**
     * @brief Enum class for command line option types.
     */
    enum Value : uint8_t {
        OPTION_TYPES(F),
        NUM_OPTION_TYPES,
        UNKNOWN_OPTION_TYPE
    };

    /**
     * @brief An iterable collection of the enum values.
     */
    static inline const std::vector<Value> ALL_TYPES = {OPTION_TYPES(F)};
#undef F

    /**
     * @brief Prefix string for a short-format option.
     */
    static inline const std::string SHORT_OPTION_PREFIX{"-"};

    /**
     * @brief Prefix string for a long-format option.
     */
    static inline const std::string LONG_OPTION_PREFIX{"--"};

    /**
     * @brief Denotes the absence of a character representation for the option.
     */
    static inline const char NULL_CHAR = '\0';

    /**
     * @brief Check if a given string is a valid option.
     *
     * @param s The string to check.
     *
     * @return True if s is a known option, false otherwise.
     */
    static bool isValid(std::string s) {
        return valueFromString(s) != UNKNOWN_OPTION_TYPE;
    }

    /**
     * @brief Initialise an Option Type directly from the enum.
     *
     * Allows the end user to write code like this:
     *
     *   OptionType o = OptionType::local;
     *
     * @param optionType The option type to initialise.
     */
    OptionType(Value optionType) : m_value(optionType) {}

    /**
     * @brief Initialise an Option Type from its string representation.
     *
     * @param s String to convert to an Option.
     */
    OptionType(const std::string &s)
        : m_value(valueFromString(s)), m_shortOption(s.size() == 1) {}

    /**
     * @brief Initialise an Option Type from its character representation.
     *
     * @param c Character to convert to an Option.
     */
    OptionType(char c) : OptionType(std::string(1, c)) {}

    /**
     * @brief Allows usage in switch and comparison statements.
     *
     * constexpr is not used here as it causes clang to stop warning on
     * incomplete case handling.
     *
     * @return Wrapped enum value.
     */
    operator Value() const { return m_value; }

    /**
     * @brief Prevent usage as a conditional statement.
     *
     * @return N/A
     */
    explicit operator bool() = delete;

    /**
     * @brief Output an option type to a given stream.
     *
     * @param stream The stream to use.
     * @param optionType The option type to use.
     *
     * @return The given stream.
     */
    friend std::ostream &operator<<(std::ostream &stream,
                                    const OptionType &optionType) {
        stream << optionType.toString();
        return stream;
    }

    /**
     * @brief Convert the Option Type to its name representation.
     *
     * @return The string representation of the Option Type.
     */
    std::string toString() const {
        if (m_value >= NUM_OPTION_TYPES) {
            return "";
        }

        if (m_shortOption) {
            return SHORT_OPTION_PREFIX + this->getCharRepresentation();
        }

        return LONG_OPTION_PREFIX + m_optionNames[m_value];
    }

    /**
     * @brief Get the parameter count for the option type.
     *
     * @return The parameter count or 0 if the option type is unknown.
     */
    constexpr uint8_t getParamCount() const {
        return (m_value < NUM_OPTION_TYPES) ? m_paramCount[m_value] : 0;
    }

    /**
     * @brief Get the single character representation of the Option Type.
     *
     * @return The corresponding character, or NULL_CHAR if none is found.
     */
    constexpr char getCharRepresentation() const {
        switch (m_value) {
        case all:
            return 'a';
        case global:
            return 'g';
        case local:
            return 'l';
        default:
            return NULL_CHAR;
        }
    }

    /**
     * @brief Whether the Option Type has a single character representation.
     *
     * @return True if a single character representation can be found.
     */
    constexpr bool hasCharRepresentation() const {
        return this->getCharRepresentation() != NULL_CHAR;
    }

  private:
#define F(s, n) #s
    /* String representations of the enum values. */
    static inline const std::vector<std::string> m_optionNames = {
        OPTION_TYPES(F)};
#undef F

#define F(e, n) n
    /**
     * @brief A mapping of the enum values to their parameter count.
     */
    static inline const std::vector<uint8_t> m_paramCount = {OPTION_TYPES(F)};
#undef F

    Value m_value;

    bool m_shortOption = false;

    /**
     * @brief Convert a string to a Value.
     *
     * @param s String to convert.
     *
     * @return The matching Value, or UNKNOWN_OPTION_TYPE if string is unknown.
     */
    static Value valueFromString(const std::string &s) {
        if (s.length() == 1) {
            for (OptionType const o : ALL_TYPES) {
                if (o.getCharRepresentation() == s[0]) {
                    return o.m_value;
                }
            }
        } else {
            auto i = std::find(m_optionNames.begin(), m_optionNames.end(), s);
            if (i != m_optionNames.end()) {
                return Value(i - m_optionNames.begin());
            }
        }

        return UNKNOWN_OPTION_TYPE;
    }
};

#undef OPTION_TYPES

} // namespace input

#endif
