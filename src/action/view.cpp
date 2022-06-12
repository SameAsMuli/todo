#include <fstream>   // std::ifstream
#include <iostream>  // std::cout
#include <stdexcept> // std::logic_error

#include "action/view.hpp"
#include "error/unknown_argument.hpp"
#include "input/option.hpp"
#include "task/task.hpp"
#include "util/display.hpp"

namespace {

const std::string ARG_NAME = "TODO type";
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
        view(taskType, false);
    } else {
        view(taskType, input.hasOption(input::Option::global));
    }
}

/**
 * @brief Print all complete tasks.
 *
 * @param input The user's input.
 */
void completeTodos(input::Input input) {
    viewTodos(input, todo::task::Type::done);
    viewTodos(input, todo::task::Type::rejected);
}

/**
 * @brief Print all outstanding tasks.
 *
 * @param input The user's input.
 */
void outstandingTodos(input::Input input) {
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
        outstandingTodos(input);
        completeTodos(input);
        return;
    }

    auto arg = input.getActionArg(0);

    if (arg == ARG_VAL_COMPLETE) {
        completeTodos(input);
    } else if (arg == ARG_VAL_OUTSTANDING) {
        outstandingTodos(input);
    } else {
        task::Type taskType{arg};

        if (taskType == task::Type::UNKNOWN_TYPE) {
            throw error::UnknownArgument(arg, ARG_NAME);
        }

        viewTodos(input, taskType);
    }
}

std::string View::usage() const {
    return "usage: todo " + this->getName() + " [<" + ARG_NAME + ">]";
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
         << "' is given, then all complete TODOs will be displayed. If a TODO "
            "type of '"
         << ARG_VAL_OUTSTANDING
         << "' is given, then all outstanding TODOs will be displayed.";

    return desc.str();
}

} // namespace action
} // namespace todo
