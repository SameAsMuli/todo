#include <algorithm>    // std::find_if, std::transform
#include <cctype>       // std::isspace
#include <charconv>     // std::from_chars
#include <cstring>      // std::strcmp
#include <stdexcept>    // std::runtime_error
#include <system_error> // std::errc

#include "SafeInt.hpp"

#include "util/string.hpp"

namespace util {
namespace string {

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
        throw std::runtime_error("Invalid number: '" + input + "'");
    }
    return value;
}

std::string toupper(const std::string &input) {
    auto str = std::string(input);
    std::transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;
}

std::string wrap(const std::string &input, int width) {
    std::string::size_type safeIndex;
    if (!SafeCast(width, safeIndex)) {
        throw std::runtime_error{"Invalid width passed to util::string::wrap"};
    }

    std::string::size_type newlinePos = 0;
    std::string::size_type spacePos = 0;
    auto str = std::string(input);

    /* Loop till the last line is less than 'width' number of characters long */
    while (width < input.length() - spacePos) {
        /* Check where the last newline character was */
        newlinePos = str.rfind('\n', spacePos + width);

        if (newlinePos == std::string::npos || newlinePos == spacePos) {
            /* The current line is longer than 'width' number of characters so
             * split it at the last space character before exceeding 'width'.
             */
            spacePos = str.rfind(' ', spacePos + width);

            if (newlinePos == std::string::npos ||
                (spacePos != std::string::npos && spacePos > newlinePos)) {
                str.at(spacePos) = '\n';

            } else {
                /* There are no space characters in the next 'width' number of
                 * characters so look for the next appropriate place to split.
                 */
                spacePos = str.find(' ', spacePos + width);

                if (spacePos == std::string::npos) {
                    /* No more spaces in the string, so stop here */
                    break;
                }

                newlinePos = str.find('\n', spacePos + width);

                if (spacePos < newlinePos) {
                    str.at(spacePos) = '\n';
                } else {
                    spacePos = newlinePos;
                }
            }

        } else {
            /* There was a newline character within 'width' number of characters
             * from the start of the line, so we don't need to wrap this line
             * and can now start counting from that point.
             */
            spacePos = newlinePos;
        }
    }

    return str;
}

} // namespace string
} // namespace util
