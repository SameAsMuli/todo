#ifndef TASK_PREFIX_H
#define TASK_PREFIX_H

#include <algorithm> // std::find
#include <iostream>  // std::ostream
#include <string>    // std::string
#include <vector>    // std::vector

namespace todo {
namespace task {

/**
 * Define the list of task prefixes with their character representation.
 */
#define PREFIXES(F)                                                            \
    F(low, '~'), F(normal, '-'), F(high, '!'), F(urgent, '#'), F(done, '+'),   \
        F(rejected, '/')

/**
 * @brief A class to describe the available task prefixes.
 *
 * The class acts as a wrapper around an enum. The enum describes all possible
 * prefixes for any task, which allows consistency when using the same
 * prefixes across different tasks.
 *
 * Prefixes are represented as a single character at the start of a task.
 *
 */
class Prefix {

  public:
#define F(e, d) e
    /**
     * @brief Enum class for command line prefixes.
     */
    enum Value : uint8_t { PREFIXES(F), NUM_PREFIXES, UNKNOWN_PREFIX };

    /**
     * @brief An iterable collection of the enum values.
     */
    static inline const std::vector<Value> ALL_PREFIXES = {PREFIXES(F)};
#undef F

    /**
     * @brief Denotes the absence of a character representation for the prefix.
     */
    static inline const char NULL_CHAR = ' ';

    /**
     * @brief Check if a given character is a valid prefix.
     *
     * @param c The character to check.
     *
     * @return True if c is a known prefix, false otherwise.
     */
    static bool isValid(char c) { return valueFromChar(c) != UNKNOWN_PREFIX; }

    /**
     * @brief Default constructor for a Prefix.
     */
    Prefix() : m_value(UNKNOWN_PREFIX) {}

    /**
     * @brief Initialise a Prefix directly from the enum.
     *
     * Allows the end user to write code like this:
     *
     *   Prefix p = Prefix::urgent;
     *
     * @param prefix The prefix to initialise.
     */
    Prefix(Value prefix) : m_value(prefix) {}

    /**
     * @brief Initialise a Prefix from its character representation.
     *
     * @param c Character to convert to a Prefix.
     */
    Prefix(char c) : m_value(valueFromChar(c)) {}

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
     * @brief Define equality between Prefix objects.
     *
     * @param other The other Prefix to compare to this one.
     *
     * @return True if the Value of both Prefixes is equal, false otherwise.
     */
    bool operator==(const Prefix &other) { return m_value == (Value)other; }

    /**
     * @brief Define equality between a Prefix object and a Value.
     *
     * Allows the end user to write code like this:
     *
     *   Prefix prefix{'!'};
     *   if (prefix == Prefix::high) { ... }
     *
     * @param value The Prefix value to compare against.
     *
     * @return True if the Prefix's value matches value, false otherwise.
     */
    bool operator==(const Value &value) { return m_value == value; }

    /**
     * @brief Prevent usage as a conditional statement.
     *
     * @return N/A
     */
    explicit operator bool() = delete;

    /**
     * @brief Populate the prefix from a stream.
     *
     * Takes the first character from the stream and uses that as the prefix
     * character. If that character is not recognised, then UNKNOWN_PREFIX is
     * used.
     *
     * @param stream The stream to use.
     * @param prefix The prefix object to populate.
     *
     * @return The given stream.
     */
    friend std::istream &operator>>(std::istream &stream, Prefix &prefix) {
        char character = stream.get();

        if (character == EOF) {
            /* Stream is empty when it wasn't expected it to be, so set the
             * failbit
             */
            stream.setstate(std::ios::failbit);
        } else {
            prefix.m_value = valueFromChar(character);
        }

        return stream;
    }

    /**
     * @brief Output a prefix to a given stream.
     *
     * @param stream The stream to use.
     * @param prefix The prefix to use.
     *
     * @return The given stream.
     */
    friend std::ostream &operator<<(std::ostream &stream,
                                    const Prefix &prefix) {
        stream << prefix.getCharRepresentation();
        return stream;
    }

    /**
     * @brief Convert the Prefix to its task name representation.
     *
     * @return The string representation of the Prefix.
     */
    std::string toString() const {
        if (m_value >= NUM_PREFIXES) {
            return "";
        }

        return m_prefixNames[m_value];
    }

    /**
     * @brief Get the single character representation of the Prefix.
     *
     * @return The corresponding character, or NULL_CHAR if none is found.
     */
    constexpr char getCharRepresentation() const {
        if (m_value >= NUM_PREFIXES) {
            return NULL_CHAR;
        }

        return this->m_prefixDesc[m_value];
    }

  private:
#define F(e, c) #e
    /* String representations of the enum values. */
    static inline const std::vector<std::string> m_prefixNames = {PREFIXES(F)};
#undef F

#define F(e, c) c
    /**
     * @brief A mapping of the enum values to their description.
     */
    static inline const std::vector<char> m_prefixDesc = {PREFIXES(F)};
#undef F

    Value m_value;

    bool m_shortPrefix = false;

    /**
     * @brief Convert a character to a Value.
     *
     * @param c Character to convert.
     *
     * @return The matching Value, or UNKNOWN_PREFIX if character is unknown.
     */
    static Value valueFromChar(char c) {
        for (Prefix const o : ALL_PREFIXES) {
            if (o.getCharRepresentation() == c) {
                return o.m_value;
            }
        }

        return UNKNOWN_PREFIX;
    }
};

#undef PREFIXES

} // namespace task
} // namespace todo

namespace std {

/**
 * @brief Define a hash for the Prefix class.
 */
template <> struct hash<todo::task::Prefix> {
    /**
     * @brief Define the hashing function for the Prefix class.
     *
     * As the class is effectively just an enum we only need to case Value to a
     * size_t type to create an effective hash.
     *
     * @param prefix The prefix to hash.
     *
     * @return A hash of the given prefix.
     */
    size_t operator()(const todo::task::Prefix &prefix) const {
        return static_cast<std::size_t>(prefix);
    }
};

} // namespace std

#endif
