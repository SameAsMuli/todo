#include <algorithm> // std::min, std::sort
#include <iostream>
#include <sstream>     // std::stringstream
#include <sys/ioctl.h> // struct winsize, TIOCGWINSZ

#include "config/version.hpp"
#include "file/definitions.hpp"
#include "util/display.hpp"
#include "util/string.hpp"

namespace {

unsigned int get_terminal_width() {
    struct winsize w;
    ioctl(fileno(stdin), TIOCGWINSZ, &w);
    return w.ws_col;
}

} // namespace

namespace util {
namespace display {

std::string header() { return "TODO Management Utility - v" + todo::version(); }

std::string footer() { return "Written by Sam Amis"; }

std::string
program_overview(std::vector<std::pair<std::string, std::string>> actions) {
    std::string::size_type maxNameLen = 0;
    std::string::size_type minSeparatorLen = 3;

    maxNameLen =
        std::max_element(actions.begin(), actions.end(), [](auto a, auto b) {
            return a.first.size() < b.first.size();
        })->first.size();

    std::stringstream ss;

    ss << header() << std::endl;

    ss << std::endl;
    ss << program_usage() << std::endl;

    ss << std::endl;
    ss << wrap(
              "By default, each action will look in the current directory, and "
              "each subsequent parent directory, until a directory containing "
              "TODO information is found.\n\n"
              "If the home directory is reached and no TODO information is "
              "found, then the action will use the global todo directory. On "
              "this system this is configured as:\n\n'" +
                  std::string(todo::file::get_todo_dir(true)) + "'",
              WIDTH)
       << std::endl;

    ss << std::endl;
    ss << wrap("If run with no arguments, then the view action is used as a "
               "default.",
               WIDTH)
       << std::endl;

    ss << std::endl;
    ss << "List of actions:" << std::endl;

    /* Make sure the actions are in alphabetical order */
    std::sort(actions.begin(), actions.end(),
              [](auto a1, auto a2) { return a1.first < a2.first; });

    for (const auto &action : actions) {
        ss << INDENT + action.first + " " +
                  std::string(minSeparatorLen +
                                  (maxNameLen - action.first.size()),
                              '.') +
                  " " + action.second
           << std::endl;
    }

    ss << std::endl;
    ss << footer();

    return ss.str();
}

std::string program_usage() {
    return "usage: todo [<action>] [<options>] [<args>]\n"
           "            [--help] [<action>]";
}

std::string program_version() { return "todo version " + todo::version(); }

std::string wrap(const std::string &input, std::optional<unsigned int> maxWidth,
                 unsigned int indentWidth) {
    auto termWidth = get_terminal_width();
    auto width = maxWidth.has_value() ? std::min(termWidth, maxWidth.value())
                                      : termWidth;
    return util::string::wrap(input, width, indentWidth);
}

} // namespace display
} // namespace util
