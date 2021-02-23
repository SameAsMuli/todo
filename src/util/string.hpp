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

} // namespace string
} // namespace util

#endif
