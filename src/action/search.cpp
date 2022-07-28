#include <algorithm> // std::sort
#include <vector>    // std::vector

#include "action/search.hpp"
#include "error/incompatible_options.hpp"
#include "file/definitions.hpp"
#include "file/file.hpp"
#include "file/tasks_data.hpp"
#include "task/task.hpp"

namespace {

std::function<bool(const todo::task::Task &)>
getSearchFunc(std::string searchString, bool exact) {
    if (exact) {
        return [searchString](const auto &task) {
            return task.getDescription() == searchString;
        };
    }
    return [searchString](const auto &task) {
        return task.getDescription().find(searchString) != std::string::npos;
    };
}

std::vector<todo::task::Task> searchTasks(const todo::file::TasksData &tasks,
                                          const std::string &searchString,
                                          bool exact) {
    return tasks.search(getSearchFunc(searchString, exact));
}

} // namespace

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
    bool all = input.hasOption(input::Option::all);
    bool exact = input.hasOption(input::Option::exact);
    bool global = input.hasOption(input::Option::global);

    /* Sense check the options */
    if (all && global) {
        throw error::IncompatibleOptions(input::Option::all,
                                         input::Option::global);
    }

    std::vector<task::Task> searchResults;
    std::string searchString = input.getActionArgString();

    /* Search for matching tasks */
    if (all) {
        searchResults = searchTasks(file::TasksData{file::File::tasks, true},
                                    searchString, exact);

        if (file::getTodoDir(false) != file::getTodoDir(true)) {
            auto matchingTasks = searchTasks(
                file::TasksData{file::File::tasks, false}, searchString, exact);
            searchResults.insert(searchResults.end(), matchingTasks.begin(),
                                 matchingTasks.end());
        }
    } else {
        searchResults = searchTasks(file::TasksData{file::File::tasks, global},
                                    searchString, exact);
    }

    /* Sort the list by descending priority and time added */
    std::sort(searchResults.begin(), searchResults.end(),
              [](const auto &lhs, const auto &rhs) {
                  if (lhs.getType() == rhs.getType()) {
                      return lhs.getTimeAdded() < rhs.getTimeAdded();
                  }
                  return lhs.getType() < rhs.getType();
              });

    for (auto const task : searchResults) {
        std::cout << task << std::endl;
    }
}

} // namespace action
} // namespace todo
