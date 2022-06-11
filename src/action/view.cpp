#include <fstream>   // std::ifstream
#include <iostream>  // std::cout
#include <stdexcept> // std::logic_error

#include "action/view.hpp"
#include "error/unknown_argument.hpp"
#include "input/option.hpp"
#include "task/task.hpp"

namespace {

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

} // namespace

namespace todo {
namespace action {

View::View() : ActionAbstract("view", "View outstanding TODOs", 1) {
    this->addValidOption(input::Option::all);
    this->addValidOption(input::Option::global);
}

void View::run(const input::Input &input) {
    if (input.getActionArgCount() == 0) {
        this->outstandingTodos(input);
        this->completeTodos(input);
        return;
    }

    auto arg = input.getActionArg(0);

    if (arg == "complete") {
        this->completeTodos(input);
    } else if (arg == "outstanding") {
        this->outstandingTodos(input);
    } else if (arg == "urgent") {
        this->urgentTodos(input);
    } else if (arg == "high") {
        this->highTodos(input);
    } else if (arg == "normal") {
        this->normalTodos(input);
    } else if (arg == "low") {
        this->lowTodos(input);
    } else if (arg == "done") {
        this->doneTodos(input);
    } else if (arg == "reject") {
        this->rejectTodos(input);
    } else {
        throw error::UnknownArgument(arg, "task type");
    }
}

void View::completeTodos(input::Input input) const {
    this->doneTodos(input);
    this->rejectTodos(input);
}

void View::outstandingTodos(input::Input input) const {
    this->urgentTodos(input);
    this->highTodos(input);
    this->normalTodos(input);
    this->lowTodos(input);
}

void View::doneTodos(input::Input input) const {
    viewTodos(input, task::Type::done);
}

void View::highTodos(input::Input input) const {
    viewTodos(input, task::Type::high);
}

void View::lowTodos(input::Input input) const {
    viewTodos(input, task::Type::low);
}

void View::normalTodos(input::Input input) const {
    viewTodos(input, task::Type::normal);
}

void View::rejectTodos(input::Input input) const {
    viewTodos(input, task::Type::rejected);
}

void View::urgentTodos(input::Input input) const {
    viewTodos(input, task::Type::urgent);
}

} // namespace action
} // namespace todo
