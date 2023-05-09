#include <algorithm>    // std::find_if, std::min, std::transform
#include <cctype>       // std::isspace
#include <charconv>     // std::from_chars
#include <cstring>      // std::strcmp
#include <stdexcept>    // std::runtime_error
#include <system_error> // std::errc

#include "util/string.hpp"

namespace util {
namespace string {

int demerau_levenshtein_distance(const std::string &str1,
                                 const std::string &str2) {
    auto len1 = str1.length();
    auto len2 = str2.length();

    if (len1 == 0)
        return len2;
    if (len2 == 0)
        return len1;

    int dist[len1 + 1][len2 + 1];

    /* Initialise the matrix */
    for (int i = 0; i <= len1; i++)
        dist[i][0] = i;

    for (int j = 0; j <= len2; j++)
        dist[0][j] = j;

    /* Compare substrings of increasing length to find minimum distance */
    for (int i = 1; i <= len1; i++) {
        for (int j = 1; j <= len2; j++) {
            if (str1[i - 1] == str2[j - 1]) {
                dist[i][j] = dist[i - 1][j - 1]; // no operation
            } else {
                if (str1[i] == str2[j - 1] && str1[i - 1] == str2[j]) {
                    dist[i][j] = dist[i - 1][j - 1]; // transpose chars
                } else {
                    dist[i][j] =
                        std::min(std::min(dist[i - 1][j],  // delete char
                                          dist[i][j - 1]), // insert char
                                 dist[i - 1][j - 1]        // substitute char
                                 ) +
                        1;
                }
            }
        }
    }

    return dist[len1][len2];
}

std::vector<std::string> corrections(const std::string &input,
                                     const std::vector<std::string> &dictionary,
                                     unsigned int max_distance) {
    std::vector<std::pair<std::string, unsigned int>> weighted_suggestions;

    for (int i = 0; i < dictionary.size(); i++) {
        auto suggestion = dictionary[i];

        /* Ignore empty suggestions */
        if (suggestion.size() == 0) {
            continue;
        }

        auto dist =
            util::string::demerau_levenshtein_distance(input, suggestion);

        /* For an exact match, there's no need to return any corrections */
        if (dist == 0) {
            return {};
        }

        if (dist <= max_distance) {
            weighted_suggestions.push_back({suggestion, dist});
        }
    }

    /* Sort the suggestions by ascending distance, and then alphabetically */
    std::sort(weighted_suggestions.begin(), weighted_suggestions.end(),
              [](std::pair<std::string, unsigned int> a,
                 std::pair<std::string, unsigned int> b) {
                  if (a.second == b.second) {
                      return a.first < b.first;
                  }
                  return a.second < b.second;
              });

    std::vector<std::string> suggestions;
    for (const auto &[suggestion, _] : weighted_suggestions) {
        /* Guard against repeats in the dictionary */
        if (std::find(suggestions.begin(), suggestions.end(), suggestion) ==
            suggestions.end())
            suggestions.push_back(suggestion);
    }

    return suggestions;
}

void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
                return !std::isspace(ch);
            }));
}

std::string ltrim_copy(std::string s) {
    ltrim(s);
    return s;
}

void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
                         [](unsigned char ch) { return !std::isspace(ch); })
                .base(),
            s.end());
}

std::string rtrim_copy(std::string s) {
    rtrim(s);
    return s;
}

void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}

std::string trim_copy(std::string s) {
    trim(s);
    return s;
}

int toint(const std::string &input) {
    int value = 0;
    auto [p, ec] =
        std::from_chars(input.data(), input.data() + input.size(), value);
    if (ec != std::errc() || std::strcmp(p, "\0") != 0) {
        throw std::runtime_error("invalid number: '" + input + "'");
    }
    return value;
}

std::string toupper(const std::string &input) {
    auto str = std::string(input);
    std::transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;
}

std::string wrap(const std::string &input, unsigned int maxWidth,
                 unsigned int indentWidth) {
    if (maxWidth <= indentWidth) {
        throw std::runtime_error{
            "smaller maxWidth than indentWidth passed to util::string::wrap"};
    }

    std::string::size_type breakPos = 0;
    bool firstLine = true;
    std::string::size_type lineStartPos = 0;
    std::string::size_type newlinePos;
    std::string::size_type spacePos = 0;
    auto str = std::string(input);

    /* Loop till last line is maxWidth or less number of characters long */
    while (lineStartPos != std::string::npos &&
           str.length() - lineStartPos > maxWidth) {
        /* Check for a newline character within the next maxWidth characters */
        newlinePos = str.rfind('\n', lineStartPos + maxWidth);

        if (newlinePos == std::string::npos || newlinePos <= lineStartPos) {
            /* The current line is longer than maxWidth, find the latest
             * available space character on which to break */
            spacePos = str.rfind(' ', lineStartPos + maxWidth);

            if (spacePos != std::string::npos && spacePos > lineStartPos) {
                /* String has a space character within the next maxWidth
                 * characters, replace with a newline */
                str.at(spacePos) = '\n';
                breakPos = spacePos;
            } else {
                /* Next word in string is longer than maxWidth, find the next
                 * appropriate place to break */
                newlinePos = str.find('\n', lineStartPos + 1);
                spacePos = str.find(' ', lineStartPos + 1);

                if (newlinePos != std::string::npos) {
                    if (spacePos == std::string::npos ||
                        newlinePos < spacePos) {
                        /* Next appropriate character is a newline */
                        breakPos = newlinePos;
                    } else {
                        /* Next appropriate character is a space, break there */
                        str.at(spacePos) = '\n';
                        breakPos = spacePos;
                    }
                } else if (spacePos != std::string::npos) {
                    /* Next appropriate character is a space, break there */
                    str.at(spacePos) = '\n';
                    breakPos = spacePos;
                } else {
                    /* Remainder of string is a single word */
                    breakPos = std::string::npos;
                }
            }
        } else {
            /* There was a newline character within 'maxWidth' number of
             * characters from the start of the line, so we don't need to
             * wrap this line and can now start counting from that point.
             */
            breakPos = newlinePos;
        }

        /* Add any indent characters */
        if (indentWidth > 0) {
            if (!firstLine) {
                /* If we've added a newline, indent the previous line */
                if (breakPos != std::string::npos) {
                    str.insert(lineStartPos, std::string(indentWidth, ' '));
                    if (breakPos != std::string::npos) {
                        breakPos += indentWidth;
                    }
                }

                /* If there are no more newline characters to place, indent the
                 * final line now */
                if (breakPos == std::string::npos) {
                    str.insert(lineStartPos, std::string(indentWidth, ' '));
                }
            } else {
                /* Do not indent the first line */
                maxWidth -= indentWidth;
            }

            /* If the last newline character has been placed, indent the
             * final line now */
            if (str.length() - (breakPos + 1) <= maxWidth) {
                str.insert(breakPos + 1, std::string(indentWidth, ' '));
                breakPos += indentWidth;
            }
        }

        if (breakPos != std::string::npos)
            lineStartPos = breakPos + 1;
        else
            lineStartPos = std::string::npos;

        if (firstLine)
            firstLine = false;
    }

    return str;
}

} // namespace string
} // namespace util
