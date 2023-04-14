#ifndef UTIL_FS_H
#define UTIL_FS_H

#include <filesystem> // std::filesystem
#include <optional>   // std::optional
#include <string>     // std::string
#include <thread>     // std::thread
#include <vector>     // std::vector

namespace util {
namespace fs {

/**
 * @brief Get a list of files recursively contained by a directory.
 *
 * @param dir The top level directory to search.
 * @param files A list to populate with found files.
 */
void get_files_from_dir(const std::filesystem::path &dir,
                        std::deque<std::filesystem::path> &files);

/**
 * @brief Find the home directory for the system.
 *
 * Will check "$HOME" first before looking in the user database.
 *
 * @return The filesystem path to the home directory, or an empty path.
 */
std::filesystem::path home_dir();

/**
 * @brief Create a directory if it doesn't already exist.
 *
 * @param dir The path to the directory.
 */
void init_dir(const std::filesystem::path dir);

/**
 * @brief Create a file if it doesn't already exist.
 *
 * @param file The path to the file.
 */
void init_file(const std::filesystem::path &file);

/**
 * @brief Check if a path is executable.
 *
 * @param path The path to check.
 *
 * @return True if the path is executable, false otherwise.
 */
bool is_executable(const std::string &path);

} // namespace fs
} // namespace util

#endif
