#ifndef UTIL_XDG_H
#define UTIL_XDG_H

#include <filesystem> // std::filesystem
#include <vector>     // std::vector

namespace util {
namespace xdg {

/**
 * @brief Find the configured XDG_CONFIG_HOME directory.
 *
 * This method will first use the value of "$XDG_CONFIG_HOME" before defaulting
 * to a value of "~/.config" if the environment variable is empty.
 *
 * @return A filesystem path to the directory.
 */
std::filesystem::path configHome();

/**
 * @brief Find the configured XDG_DATA_HOME directory.
 *
 * This method will first use the value of "$XDG_DATA_HOME" before defaulting
 * to a value of "~/.local/share" if the environment variable is empty.
 *
 * @return A filesystem path to the directory.
 */
std::filesystem::path dataHome();

/* return getEnvDirs("XDG_DATA_DIRS", "/usr/local/share/:/usr/share/"); */

/**
 * @brief Find the configured list of XDG_CONFIG_DIRS.
 *
 * This method will first use the value of "$XDG_CONFIG_DIRS" before defaulting
 * to a value of "/etc/xdg" if the environment variable is empty.
 *
 * @return A vector of filesystem paths to the directories.
 */
std::vector<std::filesystem::path> configDirs();

/**
 * @brief Find the configured list of XDG_DATA_DIRS.
 *
 * This method will first use the value of "$XDG_DATA_DIRS" before defaulting
 * to a value of "/usr/local/share/:/usr/share/" if the environment variable is
 * empty.
 *
 * @return A vector of filesystem paths to the directories.
 */
std::vector<std::filesystem::path> dataDirs();

/**
 * @brief Find the configured XDG_CACHE_HOME directory.
 *
 * This method will first use the value of "$XDG_CACHE_HOME" before defaulting
 * to a value of "~/.cache" if the environment variable is empty.
 *
 * @return A filesystem path to the directory.
 */
std::filesystem::path cacheHome();

/**
 * @brief Find the configured XDG_RUNTIME_DIR directory.
 *
 * This method will first use the value of "$XDG_RUNTIME_DIR". This needs to be
 * set, we cannot rely on a default. If the environment variable is not
 * configured then a runtime error is thrown.
 *
 * @return A filesystem path to the directory.
 */
std::filesystem::path runtimeDir();

} // namespace xdg
} // namespace util

#endif
