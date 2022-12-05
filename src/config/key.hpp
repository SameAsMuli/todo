#ifndef CONFIG_KEY_H
#define CONFIG_KEY_H

#include <algorithm> // std::find
#include <iostream>  // std::istream, std::ostream
#include <sstream>   // std::istringstream
#include <string>    // std::string
#include <vector>    // std::vector

namespace {

inline bool str_to_bool(const std::string &str) {
    bool b;
    std::istringstream{str} >> std::boolalpha >> b;
    return b;
}

template <typename T> T str_to_vector(const std::string &str) {
    std::vector<T> v;
    std::stringstream ss(str);
    T value;
    while (ss >> value) {
        v.push_back(value);

        if (ss.peek() == ',')
            ss.ignore();
    }
    return v;
}

} // namespace

namespace todo {
namespace config {

enum ConfigType {
    boolean,
    integer,
    real,
    string,
    array_boolean,
    array_integer,
    array_real,
    array_string
};

/**
 * Define the list of config keys with their type and descriptions.
 */
#define KEYS_INT(F)                                                            \
    F(archive_timeout, integer,                                                \
      "Archive tasks completed more than this many minutes ago", 1440)

#define KEYS_STR(F)                                                            \
    F(todo_string, string,                                                     \
      "The text to search for when finding TODOs in files", "TODO")

#define KEYS(F) KEYS_INT(F), KEYS_STR(F)

/**
 * @brief A class to describe the available keys for key-value configuration.
 *
 * The class acts as a wrapper around an enum. The enum describes all possible
 * keys that could be used for configuration, which allows consistency when
 * using the same keys across different areas of the code.
 */
class Key {

  public:
#define F(enum_val, type, description, default_val) enum_val
    /**
     * @brief Enum class for configuration keys.
     */
    enum Value : uint8_t { KEYS(F), NUM_KEYS, UNKNOWN_KEY };

    /**
     * @brief An iterable collection of the enum values.
     */
    static inline const std::vector<Value> ALL_TYPES = {KEYS(F)};
#undef F

    /**
     * @brief Default constructor for a Key.
     */
    Key() : m_value(UNKNOWN_KEY) {}

    /**
     * @brief Initialise a Key directly from the enum.
     *
     * This is intentionally not an explicit constructor, which allows the end
     * user to write code like this:
     *
     *   Key k = Key::archive_time;
     *
     * @param key The key to initialise.
     */
    Key(Value key) : m_value(key) {}

    /**
     * @brief Initialise a Key from its string representation.
     *
     * @param str String to convert to a Key.
     */
    explicit Key(std::string str) : m_value(value_from_string(str)) {}

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
     * @brief Define equality between Key objects.
     *
     * @param other The other Key to compare to this one.
     *
     * @return True if the Value of both Keys is equal, false otherwise.
     */
    bool operator==(const Key &other) { return m_value == (Value)other; }

    /**
     * @brief Define equality between a Key object and a Value.
     *
     * Allows the end user to write code like this:
     *
     *   Key key{'!'};
     *   if (key == Key::archive_time) { ... }
     *
     * @param value The Key value to compare against.
     *
     * @return True if the Key's value matches value, false otherwise.
     */
    bool operator==(const Value &value) { return m_value == value; }

    /**
     * @brief Prevent usage as a conditional statement.
     *
     * @return N/A
     */
    explicit operator bool() = delete;

    /**
     * @brief Output a key to a given stream.
     *
     * @param stream The stream to use.
     * @param key The key to use.
     *
     * @return The given stream.
     */
    friend std::ostream &operator<<(std::ostream &stream, const Key &key) {
        stream << key.to_string();
        return stream;
    }

    /**
     * @brief Convert the Key to its task name representation.
     *
     * @return The string representation of the Key.
     */
    std::string to_string() const {
        return (m_value < NUM_KEYS) ? m_keyNames[m_value] : "";
    }

    /**
     * @brief Get the configuration type of the key's value.
     *
     * @return The ConfigType for this key.
     */
    ConfigType type() const {
        return (m_value < NUM_KEYS) ? m_keyTypes[m_value] : ConfigType::string;
    }

    /**
     * @brief Get the description of the configuration key.
     *
     * @return A string detailing the purpose or usage of the configuration.
     */
    std::string description() const {
        return (m_value < NUM_KEYS) ? m_keyDescriptions[m_value] : "";
    }

    /**
     * @brief Get the default value for the configuration key.
     *
     * @param value The value reference to populate with the default.
     *
     * @{
     */
#define F(enum_val, type, description, default_val) enum_val
    void default_value(int &value) const {
        if (type() != integer) {
            throw std::logic_error{"key '" + to_string() +
                                   "' must be used with type int"};
        }
        value = m_intDefaults[m_value - first(KEYS_INT(F))];
    }

    void default_value(std::string &value) const {
        if (type() != string) {
            throw std::logic_error{"key '" + to_string() +
                                   "' must be used with type string"};
        }
        if (m_value == UNKNOWN_KEY)
            value = {};
        else
            value = m_strDefaults[m_value - first(KEYS_STR(F))];
    }
#undef F
    /* @} */

  private:
#define F(enum_val, type, description, default_val) #enum_val
    /* String representations of the enum values. */
    static inline const std::vector<std::string> m_keyNames = {KEYS(F)};
#undef F

#define F(enum_val, type, description, default_val) type
    /**
     * @brief A mapping of the enum values to their type.
     */
    static inline const std::vector<ConfigType> m_keyTypes = {KEYS(F)};
#undef F

#define F(enum_val, type, description, default_val) description
    /**
     * @brief A mapping of the enum values to their description.
     */
    static inline const std::vector<std::string> m_keyDescriptions = {KEYS(F)};
#undef F

#define F(enum_val, type, description, default_val) default_val
    /**
     * @brief Mappings of the enum values to their default values.
     *
     * @{
     */
    static inline const std::vector<int> m_intDefaults = {KEYS_INT(F)};
    static inline const std::vector<std::string> m_strDefaults = {KEYS_STR(F)};
    /* @} */
#undef F

    Value m_value;

    /**
     * @brief Convert a string to a Value.
     *
     * @param str String to convert.
     *
     * @return The matching Value, or UNKNOWN_KEY if string is unknown.
     */
    static Value value_from_string(std::string str) {
        auto i = std::find(m_keyNames.begin(), m_keyNames.end(), str);
        if (i != m_keyNames.end()) {
            return Value(i - m_keyNames.begin());
        }
        return UNKNOWN_KEY;
    }

    static Key first(const Key &key1, ...) { return key1; }
};

#undef KEYS

} // namespace config
} // namespace todo

namespace std {

/**
 * @brief Define a hash for the Key class.
 */
template <> struct hash<todo::config::Key> {
    /**
     * @brief Define the hashing function for the Key class.
     *
     * As the class is effectively just an enum we only need to case Value to a
     * size_t type to create an effective hash.
     *
     * @param key The key to hash.
     *
     * @return A hash of the given key.
     */
    size_t operator()(const todo::config::Key &key) const {
        return static_cast<std::size_t>(key);
    }
};

} // namespace std

#endif
