#include "util/display.hpp"
#include "util/string.hpp"

namespace util {
namespace display {

static int MAX_WIDTH = 50;

std::string header() { return ""; }

std::string footer() { return "\nWritten by Sam Amis"; }

std::string generalUsage() {
    return "usage: todo [action] [--options] [<args>]\n"
           "            [--help] [<action>]";
}

std::string wrap(const std::string &input) {
    return util::string::wrap(input, MAX_WIDTH);
}

} // namespace display
} // namespace util
