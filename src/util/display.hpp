#ifndef UTIL_DISPLAY_H
#define UTIL_DISPLAY_H

#include <string>  // std::string
#include <utility> // std::pair
#include <vector>  // std::vector

namespace util {
namespace display {

/**
 * @brief Indentation string containing 2 whitespace characters.
 */
static std::string INDENT = "  ";

/**
 * @brief Header to display at the top of general output.
 *
 * @return A string containing the header information.
 */
std::string header();

/**
 * @brief Footer to display at the bottom of general output.
 *
 * @return A string containing the footer information.
 */
std::string footer();

/**
 * @brief Get the general information about the program.
 *
 * @param actions A list of the available actions and thier descriptions.
 *
 * @return A string containing the overview information.
 */
std::string
programOverview(std::vector<std::pair<std::string, std::string>> actions);

/**
 * @brief Get the usage information for the program.
 *
 * @return A string containing the usage information.
 */
std::string programUsage();

/**
 * @brief Get the version information for the program.
 *
 * @return A string containing the version information.
 */
std::string programVersion();

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
