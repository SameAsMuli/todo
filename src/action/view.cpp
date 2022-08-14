#include <algorithm> // std::sort
#include <fstream>   // std::ifstream
#include <iostream>  // std::cout
#include <stdexcept> // std::logic_error
#include <vector>    // std::vector

#include "date/date.h"

#include "action/view.hpp"
#include "error/incompatible_options.hpp"
#include "error/unknown_argument.hpp"
#include "file/definitions.hpp"
#include "file/tasks_data.hpp"
#include "input/option.hpp"
#include "task/task.hpp"
#include "task/type.hpp"
#include "util/ansi.hpp"
#include "util/display.hpp"

namespace {

const std::string ARG_NAME = "TODO type";
const std::string ARG_VAL_ARCHIVE = "archive";
const std::string ARG_VAL_COMPLETE = "complete";
const std::string ARG_VAL_OUTSTANDING = "outstanding";

/**
 * @brief Print all archived tasks, of all types.
 *
 * @param tasks The list of all tasks to search.
 */
void view_archive_todos(const todo::file::TasksData &tasks) {
    /* Get all archived tasks */
    auto archivedTasks = tasks.search([](const auto &task) { return true; });

    if (archivedTasks.size() == 0)
        return;

    /* Sort the list by descending completion date */
    std::sort(archivedTasks.begin(), archivedTasks.end(),
              [](const auto &lhs, const auto &rhs) {
                  return lhs.get_time_added() > rhs.get_time_added();
              });

    /* Output the tasks in the list */
    date::sys_days date;
    for (auto const task : archivedTasks) {
        auto completionDate = date::floor<date::days>(task.get_time_added());
        if (date != completionDate) {
            date = completionDate;
            using namespace date;
            std::cout << ANSI_BOLD << "\n[" << date << "]" << ANSI_RESET
                      << std::endl;
        }
        std::cout << task << std::endl;
    }
    std::cout << std::endl;
}

/**
 * @brief Print all tasks of a given type.
 *
 * @param tasks The list of all tasks to search.
 * @param taskType The task type to match against.
 */
void view_task_type(const todo::file::TasksData &tasks,
                    const todo::task::Type taskType) {
    auto matchingTasks = tasks.search(
        [taskType](const auto &task) { return task.get_type() == taskType; });

    std::sort(matchingTasks.begin(), matchingTasks.end(),
              [](const auto &lhs, const auto &rhs) {
                  return lhs.get_time_added() < rhs.get_time_added();
              });

    for (auto const task : matchingTasks) {
        std::cout << task << std::endl;
    }
}

/**
 * @brief Print all complete tasks.
 *
 * @param tasks The list of all tasks to search.
 */
void view_complete_todos(const todo::file::TasksData &tasks) {
    view_task_type(tasks, todo::task::Type::done);
    view_task_type(tasks, todo::task::Type::rejected);
}

/**
 * @brief Print all outstanding tasks.
 *
 * @param tasks The list of all tasks to search.
 */
void viewOutstandingTodos(const todo::file::TasksData &tasks) {
    view_task_type(tasks, todo::task::Type::urgent);
    view_task_type(tasks, todo::task::Type::high);
    view_task_type(tasks, todo::task::Type::normal);
    view_task_type(tasks, todo::task::Type::low);
}

void viewTasks(input::Input input, bool global) {
    /* Read the tasks file */
    auto tasks = todo::file::TasksData{todo::file::File::tasks, global};

    /* If no input is given, show all tasks */
    if (input.get_action_arg_count() == 0) {
        viewOutstandingTodos(tasks);
        view_complete_todos(tasks);
        return;
    }

    int i = 0;
    while (input.has_action_arg(i)) {
        auto arg = input.get_action_arg(i++);

        if (arg == ARG_VAL_ARCHIVE) {
            auto archivedTasks =
                todo::file::TasksData{todo::file::File::archived_tasks, global};
            view_archive_todos(archivedTasks);
        } else if (arg == ARG_VAL_COMPLETE) {
            view_complete_todos(tasks);
        } else if (arg == ARG_VAL_OUTSTANDING) {
            viewOutstandingTodos(tasks);
        } else {
            todo::task::Type taskType{arg};

            if (taskType == todo::task::Type::UNKNOWN_TYPE) {
                throw todo::error::UnknownArgument(arg, ARG_NAME);
            }

            view_task_type(tasks, taskType);
        }
    }
}

} // namespace

namespace todo {
namespace action {

View::View() : ActionAbstract("view", "View existing TODOs") {
    this->add_valid_option(input::Option::all);
    this->add_valid_option(input::Option::global);
}

void View::run(const input::Input &input) {
    /* Sense check the options */
    bool all = input.has_option(input::Option::all);
    bool global = input.has_option(input::Option::global);

    if (all && global) {
        throw todo::error::IncompatibleOptions(input::Option::all,
                                               input::Option::global);
    }

    /* Check which tasks file to consider */
    if (all) {
        viewTasks(input, true);
        if (file::get_todo_dir(false) != file::get_todo_dir(true)) {
            viewTasks(input, false);
        }
    } else {
        viewTasks(input, global);
    }
}

std::string View::usage() const {
    return "usage: todo " + this->get_name() +
           " [outstanding|complete|archive]\n"
           "            " +
           this->get_name() + " [<" + ARG_NAME + ">]";
}

std::string View::description() const {
    std::stringstream desc;
    desc << "View existing TODOs in the specified TODO directory. If run "
            "with "
            "no arguments or options, all outstanding TODOs in the nearest "
            "TODO "
            "directory will be displayed.\n\n"
            "If the "
         << input::Option(input::Option::global).to_string()
         << " option is specified, then all outstanding TODOs from the "
            "global "
            "TODO directory will be displayed. If the "
         << input::Option(input::Option::all).to_string()
         << " option is specified, then both global and local TODOs will be "
            "displayed.\n\n"
            "If a "
         << ARG_NAME
         << " is specified, only TODOs of that type will be displayed. The "
            "following are the valid options for "
         << ARG_NAME << ":\n\n";

    for (task::Type const type : task::Type::ALL_TYPES) {
        desc << util::display::INDENT << type.to_string() << std::endl;
    }

    desc << "\nIf a " << ARG_NAME << " of '" << ARG_VAL_COMPLETE
         << "' is given, then all complete TODOs will be displayed. If a "
         << ARG_NAME << " of '" << ARG_VAL_OUTSTANDING
         << "' is given, then all outstanding TODOs will be displayed. If a "
         << ARG_NAME << " of '" << ARG_VAL_ARCHIVE
         << "' is given, then all archived TODOs will be displayed.";

    return desc.str();
}

} // namespace action
} // namespace todo
