#include "util/string.hpp"

namespace util {
namespace string {

std::string toupper(const std::string &input) {
    auto str = std::string(input);
    std::transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;
}

} // namespace string
} // namespace util
