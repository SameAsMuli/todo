#include <stdexcept> // std::logic_error

#include "action/view.hpp"
#include "error/unknown_argument.hpp"
#include "input/option.hpp"
#include "task/done.hpp"
#include "task/high.hpp"
#include "task/low.hpp"
#include "task/normal.hpp"
#include "task/rejected.hpp"
#include "task/task_type_abstract.hpp"
#include "task/urgent.hpp"

namespace {

/**
 * @brief Print all tasks of a given task type.
 *
 * @param input User input options.
 * @param taskType The task type to print.
 */
void viewTodos(input::Input input,
               todo::task::TaskTypeAbstract *const taskType) {
    if (taskType == NULL) {
        throw std::logic_error{"NULL passed to " + std::string{__func__}};
    }
    if (input.hasOption(input::Option::all)) {
        taskType->view(true);
        taskType->view(false);
    } else {
        taskType->view(input.hasOption(input::Option::global));
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
    viewTodos(input, new task::Done{});
}

void View::highTodos(input::Input input) const {
    viewTodos(input, new task::High{});
}

void View::lowTodos(input::Input input) const {
    viewTodos(input, new task::Low{});
}

void View::normalTodos(input::Input input) const {
    viewTodos(input, new task::Normal{});
}

void View::rejectTodos(input::Input input) const {
    viewTodos(input, new task::Rejected{});
}

void View::urgentTodos(input::Input input) const {
    viewTodos(input, new task::Urgent{});
}

} // namespace action
} // namespace todo
