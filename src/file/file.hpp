#ifndef FILE_TYPE_H
#define FILE_TYPE_H

#include <string> // std::string
#include <vector> // std::vector

namespace todo {
namespace file {

/**
 * Define the list of data file types.
 */
#define FILES(F) F(archived_tasks), F(config), F(tasks)

/**
 * @brief A class to describe the available data file types.
 *
 * The class acts as a wrapper around an enum. The enum describes all possible
 * data file types.
 */
class File {

  public:
#define F(enum_val) enum_val
    /**
     * @brief Enum class for data file types.
     */
    enum Value : uint8_t { FILES(F) };

    /**
     * @brief An iterable collection of the enum values.
     */
    static inline const std::vector<Value> ALL_FILES = {FILES(F)};
#undef F

    /**
     * @brief Don't allow usage of the default constructor.
     */
    File() = delete;

    /**
     * @brief Initialise a File directly from the enum.
     *
     * This is intentionally not an explicit constructor, which allows the end
     * user to write code like this:
     *
     *   File f = File::tasks;
     *
     * @param file The file to initialise.
     */
    File(Value file) : m_value(file) {}

    /**
     * @brief Allows usage in switch and comparison statements.
     *
     * @return Wrapped enum value.
     */
    operator Value() const { return m_value; }

    /**
     * @brief Define equality between File objects.
     *
     * @param other The other File to compare to this one.
     *
     * @return True if the Value of both File is equal, false otherwise.
     */
    bool operator==(const File &other) { return m_value == (Value)other; }

    /**
     * @brief Define equality between a File object and a Value.
     *
     * Allows the end user to write code like this:
     *
     *   File file{"tasks"};
     *   if (file == File::urgent) { ... }
     *
     * @param value The File value to compare against.
     *
     * @return True if the File's value matches value, false otherwise.
     */
    bool operator==(const Value &value) { return m_value == value; }

    /**
     * @brief Return the file name for a given file type.
     *
     * @return A string of the name of the associated file with this type.
     */
    std::string file_name() const { return m_fileNames[m_value]; }

  private:
#define F(enum_val) #enum_val
    /* String representations of the enum values. */
    static inline const std::vector<std::string> m_fileNames = {FILES(F)};
#undef F

    Value m_value;
};

#undef FILES

} // namespace file
} // namespace todo

namespace std {

/**
 * @brief Define a hash for the File class.
 */
template <> struct hash<todo::file::File> {
    /**
     * @brief Define the hashing function for the File class.
     *
     * As the class is effectively just an enum we only need to case Value to a
     * size_t type to create an effective hash.
     *
     * @param file The file to hash.
     *
     * @return A hash of the given file.
     */
    size_t operator()(const todo::file::File &file) const {
        return static_cast<std::size_t>(file);
    }
};

} // namespace std

#endif
