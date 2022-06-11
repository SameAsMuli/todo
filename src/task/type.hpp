#ifndef TASK_TYPE_H
#define TASK_TYPE_H

#include <algorithm>  // std::find
#include <filesystem> // std::filesystem
#include <iostream>   // std::ostream
#include <sstream>    // std::stringstream
#include <string>     // std::string
#include <vector>     // std::vector

#include "file/definitions.hpp"
#include "util/ansi.hpp"

namespace todo {
namespace task {

/**
 * Define the list of task types with their character representation, display
 * colour and any formatting.
 */
#define TYPES(F)                                                               \
    F(low, '~', ANSI_FOREGROUND_BLUE, "", "", ""),                             \
        F(normal, '-', ANSI_FOREGROUND_RED, "", "", ""),                       \
        F(high, '!', ANSI_FOREGROUND_RED, "", "", ""),                         \
        F(urgent, '#', ANSI_FOREGROUND_RED, ANSI_BOLD, ANSI_FOREGROUND_RED,    \
          ANSI_BOLD),                                                          \
        F(done, '+', ANSI_FOREGROUND_GREEN, "", "", ""),                       \
        F(rejected, '/', ANSI_FOREGROUND_RED, "", ANSI_FOREGROUND_RED, "")

/**
 * @brief A class to describe the available task types.
 *
 * The class acts as a wrapper around an enum. The enum describes all possible
 * types for any task, which allows consistency when using the same types across
 * different tasks.
 *
 * Types are represented as a single character at the start of a task.
 *
 */
class Type {

  public:
#define F(enum_val, character, char_colour, char_format, desc_colour,          \
          desc_format)                                                         \
    enum_val
    /**
     * @brief Enum class for command line types.
     */
    enum Value : uint8_t { TYPES(F), NUM_TYPES, UNKNOWN_TYPE };

    /**
     * @brief An iterable collection of the enum values.
     */
    static inline const std::vector<Value> ALL_TYPES = {TYPES(F)};
#undef F

    /**
     * @brief Denotes the absence of a character representation for the type.
     */
    static inline const char NULL_CHAR = ' ';

    /**
     * @brief Check if a given character is a valid type.
     *
     * @param c The character to check.
     *
     * @return True if c is a known type, false otherwise.
     */
    static bool isValid(char c) { return valueFromChar(c) != UNKNOWN_TYPE; }

    /**
     * @brief Default constructor for a Type.
     */
    Type() : m_value(UNKNOWN_TYPE) {}

    /**
     * @brief Initialise a Type directly from the enum.
     *
     * Allows the end user to write code like this:
     *
     *   Type t = Type::urgent;
     *
     * @param type The type to initialise.
     */
    Type(Value type) : m_value(type) {}

    /**
     * @brief Initialise a Type from its character representation.
     *
     * @param c Character to convert to a Type.
     */
    Type(char c) : m_value(valueFromChar(c)) {}

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
     * @brief Define equality between Type objects.
     *
     * @param other The other Type to compare to this one.
     *
     * @return True if the Value of both Types is equal, false otherwise.
     */
    bool operator==(const Type &other) { return m_value == (Value)other; }

    /**
     * @brief Define equality between a Type object and a Value.
     *
     * Allows the end user to write code like this:
     *
     *   Type type{'!'};
     *   if (type == Type::urgent) { ... }
     *
     * @param value The Type value to compare against.
     *
     * @return True if the Type's value matches value, false otherwise.
     */
    bool operator==(const Value &value) { return m_value == value; }

    /**
     * @brief Prevent usage as a conditional statement.
     *
     * @return N/A
     */
    explicit operator bool() = delete;

    /**
     * @brief Populate the type from a stream.
     *
     * Takes the first character from the stream and uses that as the type
     * character. If that character is not recognised, then UNKNOWN_TYPE is
     * used.
     *
     * @param stream The stream to use.
     * @param type The type object to populate.
     *
     * @return The given stream.
     */
    friend std::istream &operator>>(std::istream &stream, Type &type) {
        char character = stream.get();

        if (character == EOF) {
            /* Stream is empty when it wasn't expected it to be, so set the
             * failbit.
             */
            stream.setstate(std::ios::failbit);
        } else {
            type.m_value = valueFromChar(character);
        }

        return stream;
    }

    /**
     * @brief Output a type to a given stream.
     *
     * @param stream The stream to use.
     * @param type The type to use.
     *
     * @return The given stream.
     */
    friend std::ostream &operator<<(std::ostream &stream, const Type &type) {
        stream << type.getCharRepresentation();
        return stream;
    }

    /**
     * @brief Convert the Type to its task name representation.
     *
     * @return The string representation of the Type.
     */
    std::string toString() const {
        if (m_value >= NUM_TYPES) {
            return "";
        }

        return m_typeNames[m_value];
    }

    /**
     * @brief Get the single character representation of the Type.
     *
     * @return The corresponding character, or NULL_CHAR if none is found.
     */
    constexpr char getCharRepresentation() const {
        if (m_value >= NUM_TYPES) {
            return NULL_CHAR;
        }

        return this->m_typeChar[m_value];
    }

    /**
     * @brief Format a task's description string based on a task type.
     *
     * @param description The string to format.
     *
     * @return The formatted string.
     */
    std::string formatDescription(const std::string &description) const {
        if (m_value >= NUM_TYPES) {
            return description;
        }

        std::stringstream ss;

        ss << this->m_typeCharColour[m_value] << this->m_typeCharFormat[m_value]
           << this->getCharRepresentation() << ANSI_RESET
           << this->m_typeDescColour[m_value] << this->m_typeDescFormat[m_value]
           << " " << description << ANSI_RESET;

        return ss.str();
    }

    /**
     * @brief Whether the task type for a completed task, or an outstanding one.
     *
     * @return True if the Type is for a completed task, false otherwise.
     */
    constexpr bool isComplete() const {
        switch (m_value) {
        case done:
        case rejected:
            return true;
        default:
            return false;
        }
    }

    /**
     * @brief Get the data file into which this task type is written.
     *
     * @param global Whether to consider local or global only tasks.
     *
     * @return A filesystem path to the data file.
     */
    std::filesystem::path getFile(bool global = false) const {
        if (this->isComplete())
            return file::getComplete(global);
        else
            return file::getOutstanding(global);
    }

  private:
#define F(enum_val, character, char_colour, char_format, desc_colour,          \
          desc_format)                                                         \
#enum_val
    /* String representations of the enum values. */
    static inline const std::vector<std::string> m_typeNames = {TYPES(F)};
#undef F

#define F(enum_val, character, char_colour, char_format, desc_colour,          \
          desc_format)                                                         \
    character
    /**
     * @brief A mapping of the enum values to their display character.
     */
    static inline const std::vector<char> m_typeChar = {TYPES(F)};
#undef F

#define F(enum_val, character, char_colour, char_format, desc_colour,          \
          desc_format)                                                         \
    char_colour
    /**
     * @brief A mapping of the enum values to their character colour.
     */
    static inline const std::vector<std::string> m_typeCharColour = {TYPES(F)};
#undef F

#define F(enum_val, character, char_colour, char_format, desc_colour,          \
          desc_format)                                                         \
    char_format
    /**
     * @brief A mapping of the enum values to their character formatting.
     */
    static inline const std::vector<std::string> m_typeCharFormat = {TYPES(F)};
#undef F

#define F(enum_val, character, char_colour, char_format, desc_colour,          \
          desc_format)                                                         \
    desc_colour
    /**
     * @brief A mapping of the enum values to their description colour.
     */
    static inline const std::vector<std::string> m_typeDescColour = {TYPES(F)};
#undef F

#define F(enum_val, character, char_colour, char_format, desc_colour,          \
          desc_format)                                                         \
    desc_format
    /**
     * @brief A mapping of the enum values to their description formatting.
     */
    static inline const std::vector<std::string> m_typeDescFormat = {TYPES(F)};
#undef F

    Value m_value;

    bool m_shortType = false;

    /**
     * @brief Convert a character to a Value.
     *
     * @param c Character to convert.
     *
     * @return The matching Value, or UNKNOWN_TYPE if character is unknown.
     */
    static Value valueFromChar(char c) {
        for (Type const type : ALL_TYPES) {
            if (type.getCharRepresentation() == c) {
                return type.m_value;
            }
        }

        return UNKNOWN_TYPE;
    }
};

#undef TYPES

} // namespace task
} // namespace todo

namespace std {

/**
 * @brief Define a hash for the Type class.
 */
template <> struct hash<todo::task::Type> {
    /**
     * @brief Define the hashing function for the Type class.
     *
     * As the class is effectively just an enum we only need to case Value to a
     * size_t type to create an effective hash.
     *
     * @param type The type to hash.
     *
     * @return A hash of the given type.
     */
    size_t operator()(const todo::task::Type &type) const {
        return static_cast<std::size_t>(type);
    }
};

} // namespace std

#endif
