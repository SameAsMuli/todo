#ifndef UTIL_STRING_H
#define UTIL_STRING_H

#include <string> // std::string
#include <vector> // std::vector

namespace util {
namespace string {

/**
 * @brief Calculate the Demerau-Levenshtein Distance of two strings.
 *
 * @param str1 First string to compare.
 * @param str2 Second string to compare.
 *
 * @return An integer distance between the two strings.
 */
int demerau_levenshtein_distance(const std::string &str1,
                                 const std::string &str2);

/**
 * @brief Suggest corrections to input from a given dictionary.
 *
 * The suggestions will include any elements in the dictionary that are within a
 * given Demerau-Levenshtein distance of the input. If the input exactly matches
 * an element in the dictionary, no suggestions will be given.
 *
 * The returned suggestions will be sorted, first by increasing distance from
 * the input, and then alphabetically. There will be no duplicate suggestions,
 * even if the dictionary contained duplicates.
 *
 * @param input The string to check.
 * @param dictionary The collection of valid strings that could be suggested.
 * @param max_distance The collection of valid strings that could be suggested.
 *
 * @return A vector of suggested strings.
 */
std::vector<std::string> corrections(const std::string &input,
                                     const std::vector<std::string> &dictionary,
                                     unsigned int max_distance = 2);

/**
 * @brief Remove all leading white space from the given string.
 *
 * @param input The string to trim.
 */
void ltrim(std::string &input);

/**
 * @brief Copy a string and remove leading white space.
 *
 * @param input The string to copy and trim.
 *
 * @return A copy of the input string with leading white space removed.
 */
std::string ltrim_copy(std::string input);

/**
 * @brief Remove all trailing white space from the given string.
 *
 * @param input The string to trim.
 */
void rtrim(std::string &input);

/**
 * @brief Copy a string and remove trailing white space.
 *
 * @param input The string to copy and trim.
 *
 * @return A copy of the input string with trailing white space removed.
 */
std::string rtrim_copy(std::string input);

/**
 * @brief Remove all leading and trailing white space from a string.
 *
 * @param input The string to trim.
 */
void trim(std::string &input);

/**
 * @brief Copy a string and remove leading and trailing white space.
 *
 * @param input The string to copy and trim.
 *
 * @return A copy of the input string with leading white space removed.
 */
std::string trim_copy(std::string input);

/**
 * @brief Convert a string to an integer.
 *
 * @param input The string to convert.
 *
 * @return The integer value of the string.
 */
int toint(const std::string &input);

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
