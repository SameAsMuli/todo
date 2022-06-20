#include <algorithm> // std::sort
#include <vector>    // std::vector

#include "action/search.hpp"
#include "file/accessors.hpp"
#include "file/definitions.hpp"

namespace todo {
namespace action {

Search::Search()
    : ActionAbstract("search", "Search through outstanding TODOs") {
    this->addValidOption(input::Option::all);
    this->addValidOption(input::Option::exact);
    this->addValidOption(input::Option::global);
    this->addAlias("grep");
}

std::string Search::description() const {
    return "Search for any outstanding TODOs that match the given input. "
           "Complete TODOs will not be considered when searching. By default, "
           "the action will search the closest data file and match any TODO "
           "which is a superset of the given input.\n\n"
           "Use the " +
           input::Option(input::Option::exact).toString() +
           " option to only match TODOs that have the same description as the "
           "input, and not match against superset TODOs. Use the " +
           input::Option(input::Option::global).toString() +
           " option to search the global TODO file. Use the " +
           input::Option(input::Option::all).toString() +
           " to search both the global and local TODO files.";
}

std::string Search::usage() const {
    return "usage: todo " + this->getName() + " <task description>";
}

void Search::run(const input::Input &input) {
    std::vector<task::Task> searchResults;
    auto globalFile = todo::file::getOutstanding(true);
    auto localFile = todo::file::getOutstanding(false);

    if (globalFile != localFile && (input.hasOption(input::Option::all) ||
                                    input.hasOption(input::Option::global))) {
        /* Search global tasks */
        auto [matchingTasks, nonMatches] =
            file::search(input.getActionArgString(), globalFile,
                         input.hasOption(input::Option::exact));
        searchResults.insert(searchResults.end(), matchingTasks.begin(),
                             matchingTasks.end());
    }

    if (!input.hasOption(input::Option::global)) {
        /* Search local tasks */
        auto [matchingTasks, nonMatches] =
            file::search(input.getActionArgString(), localFile,
                         input.hasOption(input::Option::exact));
        searchResults.insert(searchResults.end(), matchingTasks.begin(),
                             matchingTasks.end());
    }

    /* Sort the list by descending priority */
    std::sort(searchResults.begin(), searchResults.end(),
              [](const auto &lhs, const auto &rhs) {
                  return lhs.getType() > rhs.getType();
              });

    for (auto const task : searchResults) {
        std::cout << task.formatted() << std::endl;
    }
}

} // namespace action
} // namespace todo
