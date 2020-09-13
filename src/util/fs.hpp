#ifndef UTIL_FS_H
#define UTIL_FS_H

#include <filesystem> // std::filesystem

namespace util {
namespace fs {

/**
 * @brief Find the home directory for the system.
 *
 * Will check "$HOME" first before looking in the user database.
 *
 * @return The filesystem path to the home directory or an empty path.
 */
std::filesystem::path HomeDir();

} // namespace fs
} // namespace util

#endif
