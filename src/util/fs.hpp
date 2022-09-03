#ifndef UTIL_FS_H
#define UTIL_FS_H

#include <filesystem> // std::filesystem

namespace util {
namespace fs {

/**
 * @brief Find the current working directory for the user.
 *
 * @return The filesystem path to the current directory, or an empty path.
 */
std::filesystem::path current_dir();

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
