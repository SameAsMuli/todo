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

    std::string::size_type n = 0;
    auto str = std::string(input);

    while (n != std::string::npos && width < input.length() - n) {
        n = str.rfind(' ', n + width);
        str.at(n) = '\n';
    }

    return str;
}

} // namespace string
} // namespace util
