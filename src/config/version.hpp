#ifndef CONFIG_VERSION_H
#define CONFIG_VERSION_H

#include <string> // std::string

namespace todo {

/**
 * @brief Get the current version number of the program.
 *
 * The program is versioned in compliance with sematic versioning.
 *
 * @return A string containing the version number.
 */
std::string version();

} // namespace todo

#endif
