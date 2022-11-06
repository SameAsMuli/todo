#ifndef INPUT_OPTION_H
#define INPUT_OPTION_H

#include <algorithm> // std::find
#include <iostream>  // std::ostream
#include <string>    // std::string
#include <vector>    // std::vector

namespace input {

/**
 * Define the list of command line options with a short description and whether
 * they take an argument (true) or act as a boolean flag (false).
 */
#define OPTIONS(F)                                                             \
    F(all, "Consider all TODOs in and above the current directory", false),    \
        F(exact, "Only match identical TODOs", false),                         \
        F(force, "Perform action on all matched TODOs", false),                \
        F(global, "Consider global TODOs only", false),                        \
        F(help, "Display this help text", false),                              \
        F(local, "Consider local TODOs only", false)

/**
 * @brief A class to describe the available command line options.
 *
 * The class acts as a wrapper around an enum. The enum describes all possible
 * options for any action, which allows consistency when using the same
 * options across different actions.
 *
 * Every option has a long name, which is passed to the program in the
 * format:
 *
 *   --longname
 *
 * A type can also be optionally given a single character reference, which is
 * defined in get_char_representation and can be passed to the program in the
 * format:
 *
 *   -l
 *
 * Options can act as a boolean flag or be passed a single argument:
 *
 *   -l argument
 *   --longname argument
 */
class Option {

  public:
#define F(e, d, a) e
    /**
     * @brief Enum class for command line options.
     */
    enum Value : uint8_t { OPTIONS(F), NUM_OPTIONS, UNKNOWN_OPTION };

    /**
     * @brief An iterable collection of the enum values.
     */
    static inline const std::vector<Value> ALL_OPTIONS = {OPTIONS(F)};
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
    static bool is_valid(std::string s) {
        return value_from_string(s) != UNKNOWN_OPTION;
    }

    /**
     * @brief Initialise an Option directly from the enum.
     *
     * This is intentionally not an explicit constructor, which allows the end
     * user to write code like this:
     *
     *   Option o = Option::local;
     *
     * @param option The option to initialise.
     */
    Option(Value option) : m_value(option) {}

    /**
     * @brief Initialise an Option from its string representation.
     *
     * @param s String to convert to an Option.
     */
    explicit Option(const std::string &s)
        : m_value(value_from_string(s)), m_shortOption(s.size() == 1) {}

    /**
     * @brief Initialise an Option from its character representation.
     *
     * @param c Character to convert to an Option.
     */
    explicit Option(char c) : Option(std::string(1, c)) {}

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
     * @brief Define equality between Option objects.
     *
     * @param other The other Option to compare to this one.
     *
     * @return True if the Value of both Options is equal, false otherwise.
     */
    bool operator==(const Option &other) { return m_value == (Value)other; }

    /**
     * @brief Define equality between an Option object and a Value.
     *
     * Allows the end user to write code like this:
     *
     *   Option option{"--global"};
     *   if (option == Option::global) { ... }
     *
     * @param value The Option value to compare against.
     *
     * @return True if the Option's value matches value, false otherwise.
     */
    bool operator==(const Value &value) { return m_value == value; }

    /**
     * @brief Prevent usage as a conditional statement.
     *
     * @return N/A
     */
    explicit operator bool() = delete;

    /**
     * @brief Output an option to a given stream.
     *
     * @param stream The stream to use.
     * @param option The option to use.
     *
     * @return The given stream.
     */
    friend std::ostream &operator<<(std::ostream &stream,
                                    const Option &option) {
        stream << option.to_string();
        return stream;
    }

    /**
     * @brief Convert the Option to its name representation.
     *
     * @return The string representation of the Option.
     */
    std::string to_string() const {
        if (m_value >= NUM_OPTIONS) {
            return "";
        }

        if (m_shortOption) {
            return SHORT_OPTION_PREFIX + this->get_char_representation();
        }

        return LONG_OPTION_PREFIX + m_optionNames[m_value];
    }

    /**
     * @brief Display the option with both long and short representations.
     *
     * @return A string describing both representations of the option.
     */
    std::string get_full_string() const {
        if (this->has_char_representation()) {
            return this->to_string() + ", -" + this->get_char_representation();
        }
        return this->to_string();
    }

    /**
     * @brief Whether the Option is a boolean flag or accepts an argument.
     *
     * @return True if the Option takes an argument, false otherwise.
     */
    constexpr bool requires_arg() const {
        return (m_value < NUM_OPTIONS) ? m_requires_arg[m_value] : false;
    }

    /**
     * @brief Get the single character representation of the Option.
     *
     * @return The corresponding character, or NULL_CHAR if none is found.
     */
    constexpr char get_char_representation() const {
        switch (m_value) {
        case all:
            return 'a';
        case force:
            return 'f';
        case global:
            return 'g';
        case local:
            return 'l';
        default:
            return NULL_CHAR;
        }
    }

    /**
     * @brief Whether the Option has a single character representation.
     *
     * @return True if a single character representation can be found.
     */
    constexpr bool has_char_representation() const {
        return this->get_char_representation() != NULL_CHAR;
    }

    /**
     * @brief Get the description of the option.
     *
     * @return A string describing the option's purpose.
     */
    std::string get_description() const {
        return (m_value < NUM_OPTIONS) ? m_optionDesc[m_value] : "";
    }

  private:
#define F(s, d, a) #s
    /* String representations of the enum values. */
    static inline const std::vector<std::string> m_optionNames = {OPTIONS(F)};
#undef F

#define F(e, d, a) d
    /**
     * @brief A mapping of the enum values to their description.
     */
    static inline const std::vector<std::string> m_optionDesc = {OPTIONS(F)};
#undef F

#define F(e, d, a) a
    /**
     * @brief A mapping of the enum values to whether they require an argument.
     */
    static inline const std::vector<bool> m_requires_arg = {OPTIONS(F)};
#undef F

    Value m_value;

    bool m_shortOption = false;

    /**
     * @brief Convert a string to a Value.
     *
     * @param s String to convert.
     *
     * @return The matching Value, or UNKNOWN_OPTION if string is unknown.
     */
    static Value value_from_string(const std::string &s) {
        if (s.length() == 1) {
            auto i = std::find_if(
                ALL_OPTIONS.begin(), ALL_OPTIONS.end(), [&s](const Option &o) {
                    return o.get_char_representation() == s[0];
                });

            if (i != ALL_OPTIONS.end()) {
                return Value(i - ALL_OPTIONS.begin());
            }
        } else {
            auto i = std::find(m_optionNames.begin(), m_optionNames.end(), s);
            if (i != m_optionNames.end()) {
                return Value(i - m_optionNames.begin());
            }
        }

        return UNKNOWN_OPTION;
    }
};

#undef OPTIONS

} // namespace input

namespace std {

/**
 * @brief Define a hash for the Option class.
 */
template <> struct hash<input::Option> {
    /**
     * @brief Define the hashing function for the Option class.
     *
     * As the class is effectively just an enum we only need to case Value to a
     * size_t type to create an effective hash.
     *
     * @param option The option to hash.
     *
     * @return A hash of the given option.
     */
    size_t operator()(const input::Option &option) const {
        return static_cast<std::size_t>(option);
    }
};

} // namespace std

#endif
