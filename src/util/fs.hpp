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
std::filesystem::path CurrentDir();

/**
 * @brief Find the home directory for the system.
 *
 * Will check "$HOME" first before looking in the user database.
 *
 * @return The filesystem path to the home directory, or an empty path.
 */
std::filesystem::path HomeDir();

/**
 * @brief Find the root directory for the system.
 *
 * @return The filesystem path to the root directory, or an empty path.
 */
std::filesystem::path RootDir();

} // namespace fs
} // namespace util

#endif
