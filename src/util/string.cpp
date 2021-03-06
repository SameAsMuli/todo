#include <algorithm> // std::transform
#include <stdexcept> // std::runtime_error

#include "SafeInt.hpp"

#include "util/string.hpp"

namespace util {
namespace string {

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
