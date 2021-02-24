#ifndef UTIL_STRING_H
#define UTIL_STRING_H

#include <string> // std::string

namespace util {
namespace string {

/**
 * @brief Convert a given string to entirely uppercase.
 *
 * @param input The string to convert to uppercase.
 *
 * @return A copy of the input string where every letter is uppercase.
 */
std::string toupper(const std::string &input);

/**
 * @brief Format a string so that when printed it does not exceed a given width.
 *
 * The function will only replace space characters with newlines; meaning no
 * words should be split across multiple lines. The only exception to this is
 * when the string contains a word that is longer than the given width.
 *
 * @param input The string to format.
 * @param width The maximum width of each line.
 *
 * @return A copy of the input string which the correct text wrapping.
 */
std::string wrap(const std::string &input, int width);

} // namespace string
} // namespace util

#endif
