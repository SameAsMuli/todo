#include <algorithm> // std::sort
#include <fstream>   // std::ifstream
#include <iostream>  // std::cout
#include <stdexcept> // std::logic_error
#include <vector>    // std::vector

#include "date/date.h"

#include "action/view.hpp"
#include "error/unknown_argument.hpp"
#include "file/definitions.hpp"
#include "input/option.hpp"
#include "task/task.hpp"
#include "util/ansi.hpp"
#include "util/display.hpp"

namespace {

const std::string ARG_NAME = "TODO type";
const std::string ARG_VAL_ARCHIVE = "archive";
const std::string ARG_VAL_COMPLETE = "complete";
const std::string ARG_VAL_OUTSTANDING = "outstanding";

/**
 * @brief Print all tasks of a given task type from a specific file.
 *
 * @param taskType The task type to print.
 * @param global Whether to look in the local or global data file.
 */
void view(todo::task::Type taskType, bool global) {
    std::ifstream ifs{taskType.getFile(global).string()};

    if (ifs.is_open()) {
        todo::task::Task task;
        while (ifs >> task) {
            if (taskType == task.getType()) {
                std::cout << taskType.formatDescription(task.getDescription())
                          << std::endl;
            }
        }
    }
}

/**
 * @brief Print all tasks of a given task type, based on user input.
 *
 * @param input User input options.
 * @param taskType The task type to print.
 */
void viewTodos(input::Input input, todo::task::Type taskType) {
    if (input.hasOption(input::Option::all)) {
        view(taskType, true);
        if (taskType.getFile(true) != taskType.getFile(false)) {
            view(taskType, false);
        }
    } else {
        view(taskType, input.hasOption(input::Option::global));
    }
}

/**
 * @brief Print all archived tasks, of all types.
 *
 * @param global Whether to look in the local or global data file.
 */
void viewArchiveTodos(input::Input input) {
    std::vector<todo::task::Task> archivedTasks;
    auto globalArchiveFile = todo::file::getArchive(true);
    auto localArchiveFile = todo::file::getArchive(false);

    if (localArchiveFile != globalArchiveFile &&
        (input.hasOption(input::Option::all) ||
         input.hasOption(input::Option::global))) {
        std::ifstream ifs{globalArchiveFile.string()};

        /* Add global archived tasks to the list */
        if (ifs.is_open()) {
            todo::task::Task task;
            while (ifs >> task) {
                archivedTasks.push_back(task);
            }
        }
    }

    if (!input.hasOption(input::Option::global)) {
        std::ifstream ifs{localArchiveFile.string()};

        /* Add local archived tasks to the list */
        if (ifs.is_open()) {
            todo::task::Task task;
            while (ifs >> task) {
                archivedTasks.push_back(task);
            }
        }
    }

    /* Sort the list by descending completion date */
    std::sort(archivedTasks.begin(), archivedTasks.end(),
              [](const auto &lhs, const auto &rhs) {
                  return lhs.getTimeAdded() > rhs.getTimeAdded();
              });

    /* Output the tasks in the list */
    date::sys_days date;
    for (auto const task : archivedTasks) {
        auto completionDate = date::floor<date::days>(task.getTimeAdded());
        if (date != completionDate) {
            date = completionDate;
            using namespace date;
            std::cout << ANSI_BOLD << "\n[" << date << "]" << ANSI_RESET
                      << std::endl;
        }
        std::cout << task.getType().formatDescription(task.getDescription())
                  << std::endl;
    }
    std::cout << std::endl;
}

/**
 * @brief Print all complete tasks.
 *
 * @param input The user's input.
 */
void viewCompleteTodos(input::Input input) {
    viewTodos(input, todo::task::Type::done);
    viewTodos(input, todo::task::Type::rejected);
}

/**
 * @brief Print all outstanding tasks.
 *
 * @param input The user's input.
 */
void viewOutstandingTodos(input::Input input) {
    viewTodos(input, todo::task::Type::urgent);
    viewTodos(input, todo::task::Type::high);
    viewTodos(input, todo::task::Type::normal);
    viewTodos(input, todo::task::Type::low);
}

} // namespace

namespace todo {
namespace action {

View::View() : ActionAbstract("view", "View existing TODOs", 1) {
    this->addValidOption(input::Option::all);
    this->addValidOption(input::Option::global);
}

void View::run(const input::Input &input) {
    if (input.getActionArgCount() == 0) {
        viewOutstandingTodos(input);
        viewCompleteTodos(input);
        return;
    }

    auto arg = input.getActionArg(0);

    if (arg == ARG_VAL_ARCHIVE) {
        viewArchiveTodos(input);
    } else if (arg == ARG_VAL_COMPLETE) {
        viewCompleteTodos(input);
    } else if (arg == ARG_VAL_OUTSTANDING) {
        viewOutstandingTodos(input);
    } else {
        task::Type taskType{arg};

        if (taskType == task::Type::UNKNOWN_TYPE) {
            throw error::UnknownArgument(arg, ARG_NAME);
        }

        viewTodos(input, taskType);
    }
}

std::string View::usage() const {
    return "usage: todo " + this->getName() +
           " [outstanding|complete|archive]\n"
           "            " +
           this->getName() + " [<" + ARG_NAME + ">]";
}

std::string View::description() const {
    std::stringstream desc;
    desc
        << "View existing TODOs in the specified TODO directory. If run with "
           "no arguments or options, all outstanding TODOs in the nearest TODO "
           "directory will be displayed.\n\n"
           "If the "
        << input::Option(input::Option::global).toString()
        << " option is specified, then all outstanding TODOs from the global "
           "TODO directory will be displayed. If the "
        << input::Option(input::Option::all).toString()
        << " option is specified, then both global and local TODOs will be "
           "displayed.\n\n"
           "If a "
        << ARG_NAME
        << " is specified, only TODOs of that type will be displayed. The "
           "following are the valid options for "
        << ARG_NAME << ":\n\n";

    for (task::Type const type : task::Type::ALL_TYPES) {
        desc << util::display::INDENT << type.toString() << std::endl;
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
