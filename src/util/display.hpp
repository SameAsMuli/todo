#ifndef UTIL_DISPLAY_H
#define UTIL_DISPLAY_H

#include <optional>
#include <string>  // std::string
#include <utility> // std::pair
#include <vector>  // std::vector

namespace util {
namespace display {

/**
 * @brief A default line width that can be used for consistency across output.
 */
static unsigned int WIDTH = 70;

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
 * @param actions A list of the available actions and their descriptions.
 *
 * @return A string containing the overview information.
 */
std::string
program_overview(std::vector<std::pair<std::string, std::string>> actions);

/**
 * @brief Get the usage information for the program.
 *
 * @return A string containing the usage information.
 */
std::string program_usage();

/**
 * @brief Get the version information for the program.
 *
 * @return A string containing the version information.
 */
std::string program_version();

/**
 * @brief Format a string so that when printed it does not exceed a set width.
 *
 * The function will only replace space characters with newlines; meaning no
 * words should be split across multiple lines. The only exception to this is
 * when the string contains a word that is longer than the set width.
 *
 * @param input The string to format.
 * @param maxWidth The maximum width of each line.
 * @param indentWidth The number of spaces to insert after each newline.
 *
 * If no maxWidth is given, then a default of std::nullopt is used. This is used
 * to indicate that the terminal width should be used as the max width.
 *
 * If no indentWidth is given, then a default of 0 is used.
 *
 * @return A copy of the input string which the correct text wrapping.
 */
std::string wrap(const std::string &input,
                 std::optional<unsigned int> maxWidth = std::nullopt,
                 unsigned int indentWidth = 0);

} // namespace display
} // namespace util

#endif
