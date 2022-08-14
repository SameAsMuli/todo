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
get_search_func(std::string searchString, bool exact) {
    if (exact) {
        return [searchString](const auto &task) {
            return task.get_description() == searchString;
        };
    }
    return [searchString](const auto &task) {
        return task.get_description().find(searchString) != std::string::npos;
    };
}

std::vector<todo::task::Task> search_tasks(const todo::file::TasksData &tasks,
                                           const std::string &searchString,
                                           bool exact) {
    return tasks.search(get_search_func(searchString, exact));
}

} // namespace

namespace todo {
namespace action {

Search::Search()
    : ActionAbstract("search", "Search through outstanding TODOs") {
    this->add_valid_option(input::Option::all);
    this->add_valid_option(input::Option::exact);
    this->add_valid_option(input::Option::global);
    this->add_alias("grep");
}

std::string Search::description() const {
    return "Search for any outstanding TODOs that match the given input. "
           "Complete TODOs will not be considered when searching. By default, "
           "the action will search the closest data file and match any TODO "
           "which is a superset of the given input.\n\n"
           "Use the " +
           input::Option(input::Option::exact).to_string() +
           " option to only match TODOs that have the same description as the "
           "input, and not match against superset TODOs. Use the " +
           input::Option(input::Option::global).to_string() +
           " option to search the global TODO file. Use the " +
           input::Option(input::Option::all).to_string() +
           " to search both the global and local TODO files.";
}

std::string Search::usage() const {
    return "usage: todo " + this->get_name() + " <task description>";
}

void Search::run(const input::Input &input) {
    bool all = input.has_option(input::Option::all);
    bool exact = input.has_option(input::Option::exact);
    bool global = input.has_option(input::Option::global);

    /* Sense check the options */
    if (all && global) {
        throw error::IncompatibleOptions(input::Option::all,
                                         input::Option::global);
    }

    std::vector<task::Task> searchResults;
    std::string searchString = input.get_action_arg_string();

    /* Search for matching tasks */
    if (all) {
        searchResults = search_tasks(file::TasksData{file::File::tasks, true},
                                     searchString, exact);

        if (file::get_todo_dir(false) != file::get_todo_dir(true)) {
            auto matchingTasks = search_tasks(
                file::TasksData{file::File::tasks, false}, searchString, exact);
            searchResults.insert(searchResults.end(), matchingTasks.begin(),
                                 matchingTasks.end());
        }
    } else {
        searchResults = search_tasks(file::TasksData{file::File::tasks, global},
                                     searchString, exact);
    }

    /* Sort the list by descending priority and time added */
    std::sort(searchResults.begin(), searchResults.end(),
              [](const auto &lhs, const auto &rhs) {
                  if (lhs.get_type() == rhs.get_type()) {
                      return lhs.get_time_added() < rhs.get_time_added();
                  }
                  return lhs.get_type() < rhs.get_type();
              });

    for (auto const task : searchResults) {
        std::cout << task << std::endl;
    }
}

} // namespace action
} // namespace todo
