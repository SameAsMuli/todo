#ifndef UTIL_DISPLAY_H
#define UTIL_DISPLAY_H

#include <string> // std::string

namespace util {
namespace display {

std::string header();

std::string footer();

/**
 * @brief Get the usage information for the program.
 *
 * @return A string containing the usage information.
 */
std::string generalUsage();

/**
 * @brief Format a string so that when printed it does not exceed a set width.
 *
 * The function will only replace space characters with newlines; meaning no
 * words should be split across multiple lines. The only exception to this is
 * when the string contains a word that is longer than the set width.
 *
 * @param input The string to format.
 *
 * @return A copy of the input string which the correct text wrapping.
 */
std::string wrap(const std::string &input);

} // namespace display
} // namespace util

#endif
