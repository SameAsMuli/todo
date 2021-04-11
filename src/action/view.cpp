#include <stdexcept> // std::logic_error

#include "action/view.hpp"
#include "error/unknown_argument.hpp"
#include "input/option.hpp"
#include "task/done.hpp"
#include "task/high.hpp"
#include "task/low.hpp"
#include "task/normal.hpp"
#include "task/rejected.hpp"
#include "task/urgent.hpp"

namespace todo {
namespace action {

View::View(const input::Input &input)
    : ActionAbstract("view", "View outstanding TODOs", input, 1) {
    this->addValidOption(input::Option::all);
    this->addValidOption(input::Option::global);
}

void View::run() {
    if (this->getInput().getActionArgCount() == 0) {
        this->outstandingTodos();
        this->completeTodos();
        return;
    }

    auto arg = this->getInput().getActionArg(0);

    if (arg == "complete") {
        this->completeTodos();
    } else if (arg == "outstanding") {
        this->outstandingTodos();
    } else if (arg == "urgent") {
        this->urgentTodos();
    } else if (arg == "high") {
        this->highTodos();
    } else if (arg == "normal") {
        this->normalTodos();
    } else if (arg == "low") {
        this->lowTodos();
    } else if (arg == "done") {
        this->doneTodos();
    } else if (arg == "reject") {
        this->rejectTodos();
    } else {
        throw error::UnknownArgument(arg, "task type");
    }
}

void View::completeTodos() const {
    this->doneTodos();
    this->rejectTodos();
}

void View::outstandingTodos() const {
    this->urgentTodos();
    this->highTodos();
    this->normalTodos();
    this->lowTodos();
}

void View::doneTodos() const { this->viewTodos(new task::Done{}); }

void View::highTodos() const { this->viewTodos(new task::High{}); }

void View::lowTodos() const { this->viewTodos(new task::Low{}); }

void View::normalTodos() const { this->viewTodos(new task::Normal{}); }

void View::rejectTodos() const { this->viewTodos(new task::Rejected{}); }

void View::urgentTodos() const { this->viewTodos(new task::Urgent{}); }

/* Private methods */
void View::viewTodos(task::TaskTypeAbstract *const taskType) const {
    if (taskType == NULL) {
        throw std::logic_error{"NULL passed to " + std::string{__func__}};
    }
    if (this->getInput().hasOption(input::Option::all)) {
        taskType->view(true);
        taskType->view(false);
    } else {
        taskType->view(this->getInput().hasOption(input::Option::global));
    }
}

} // namespace action
} // namespace todo
