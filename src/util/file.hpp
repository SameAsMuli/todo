#ifndef UTIL_FILE_H
#define UTIL_FILE_H

#include <filesystem> // std::filesystem
#include <fstream>    // std::ifstream

namespace util {

/**
 * @brief Utility class to read and process a single file.
 */
class File {

  public:
    /**
     * @brief File types that will be applied to a file based on its exension.
     */
    enum Type { UNKNOWN, C, CPP, JAVA, JAVASCRIPT, LUA, PYTHON, SHELL };

    /**
     * @brief Initialise the file from a given file path.
     *
     * @param file The file path to load.
     */
    File(const std::filesystem::path &file);

    /**
     * @brief Get the file tpe of the file.
     *
     * @return The File::Type of the file, may be UNKNOWN.
     */
    Type type() const { return this->m_type; };

    /**
     * @brief Count the number of lines in the file.
     *
     * @return The total number of lines found.
     */
    unsigned int line_count();

    /**
     * @brief Search a file line-by-line for a given string.
     *
     * @param string The text to search for.
     *
     * @return A list of all matching lines.
     */
    std::vector<std::string> search(const std::string &string);

  private:
    std::ifstream m_file;
    Type m_type;
};

} // namespace util

#endif
