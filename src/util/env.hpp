#ifndef UTIL_ENV_H
#define UTIL_ENV_H

#include <string> // std::string

namespace util {
namespace env {

/**
 * @brief Check if a given command is available in the system.
 *
 * @param command The command to check.
 *
 * @return True if the command is available, false otherwise.
 */
bool command_exists(const std::string &command);

} // namespace env
} // namespace util

#endif
