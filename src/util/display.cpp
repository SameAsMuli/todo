#include <algorithm> // std::sort
#include <sstream>   // std::stringstream

#include "file/definitions.hpp"
#include "util/display.hpp"
#include "util/string.hpp"

namespace {

bool actionCompare(std::pair<std::string, std::string> a1,
                   std::pair<std::string, std::string> a2) {
    return a1.first < a2.first;
}

} // namespace

namespace util {
namespace display {

static int MAX_WIDTH = 50;

std::string header() { return ""; }

std::string footer() { return "\nWritten by Sam Amis"; }

std::string programUsage() {
    return "usage: todo [action] [--options] [<args>]\n"
           "            [--help] [<action>]";
}

std::string
programOverview(std::vector<std::pair<std::string, std::string>> actions) {
    std::string::size_type maxNameLen = 0;
    std::vector<std::pair<std::string, std::string>>::size_type
        minSeparatorLen = 3;

    for (auto const &action : actions) {
        if (maxNameLen < action.first.size()) {
            maxNameLen = action.first.size();
        }
    }

    std::stringstream ss;

    ss << util::display::header() << std::endl;

    ss << "TODO Management Utility" << std::endl;
    ss << std::endl;

    ss << util::display::programUsage() << std::endl;

    ss << std::endl;
    ss << util::display::wrap(
              "If run with no arguments, then any non-archived "
              "tasks will be printed. All tasks are stored in: '" +
              std::string(todo::file::getTodoDir(true)) + "'")
       << std::endl;
    ss << std::endl;
    ss << "List of actions:" << std::endl;

    /* Make sure the actions are in alphabetical order */
    std::sort(actions.begin(), actions.end(), actionCompare);

    for (auto const &action : actions) {
        ss << "  " + action.first + " " +
                  std::string(minSeparatorLen +
                                  (maxNameLen - action.first.size()),
                              '.') +
                  " " + action.second
           << std::endl;
    }

    ss << util::display::footer();

    return ss.str();
}

std::string wrap(const std::string &input) {
    return util::string::wrap(input, MAX_WIDTH);
}

} // namespace display
} // namespace util