#include <algorithm> // std::sort
#include <sstream>   // std::stringstream

#include "config/version.hpp"
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

std::string header() { return "TODO Management Utility - v" + todo::version(); }

std::string footer() { return "Written by Sam Amis"; }

std::string
programOverview(std::vector<std::pair<std::string, std::string>> actions) {
    std::string::size_type maxNameLen = 0;
    std::string::size_type minSeparatorLen = 3;

    for (auto const &action : actions) {
        if (maxNameLen < action.first.size()) {
            maxNameLen = action.first.size();
        }
    }

    std::stringstream ss;

    ss << header() << std::endl;

    ss << std::endl;
    ss << programUsage() << std::endl;

    ss << std::endl;
    ss << wrap("By default each action will look in the current directory, and "
               "each subsequent parent directory, until a directory containing "
               "TODO information is found.\n\n"
               "If the home directory is reached and no TODO information is "
               "found, then the action will use the global todo directory. On "
               "this system this is configured as:\n\n'" +
               std::string(todo::file::getTodoDir(true)) + "'")
       << std::endl;

    ss << std::endl;
    ss << wrap("If run with no arguments, then the view action is used as a "
               "default.")
       << std::endl;

    ss << std::endl;
    ss << "List of actions:" << std::endl;

    /* Make sure the actions are in alphabetical order */
    std::sort(actions.begin(), actions.end(), actionCompare);

    for (auto const &action : actions) {
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

std::string programUsage() {
    return "usage: todo [action] [--options] [<args>]\n"
           "            [--help] [<action>]";
}

std::string programVersion() { return "todo version " + todo::version(); }

std::string wrap(const std::string &input) {
    return util::string::wrap(input, MAX_WIDTH);
}

} // namespace display
} // namespace util
