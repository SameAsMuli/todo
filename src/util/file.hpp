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
     * @brief Initialise the file from a given file path.
     *
     * @param file The file path to load.
     */
    File(const std::filesystem::path &file);

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
};

} // namespace util

#endif
