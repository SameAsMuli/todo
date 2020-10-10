#include <fstream>   // std::ifstream
#include <iostream>  // std::cout
#include <stdexcept> // std::logic_error

#include "action/view.hpp"
#include "error/unknown_argument.hpp"
#include "task/done.hpp"
#include "task/low.hpp"
#include "task/normal.hpp"
#include "task/rejected.hpp"
#include "task/urgent.hpp"

namespace action {

View::View(const util::Input &input)
    : ActionAbstract("view", "View outstanding TODOs", input, 1) {}

void View::run() {
    if (!this->getInput().hasOption(util::Input::PARAM_START_INDEX)) {
        this->urgentTodos();
        this->normalTodos();
        this->lowTodos();
        this->doneTodos();
        this->rejectTodos();
        return;
    }

    auto option = this->getInput().getOption(util::Input::PARAM_START_INDEX);

    if (option == "complete") {
        this->completeTodos();
    } else if (option == "outstanding") {
        this->outstandingTodos();
    } else if (option == "urgent") {
        this->urgentTodos();
    } else if (option == "normal") {
        this->normalTodos();
    } else if (option == "low") {
        this->lowTodos();
    } else if (option == "done") {
        this->doneTodos();
    } else if (option == "reject") {
        this->rejectTodos();
    } else {
        throw todo::error::UnknownArgument(option);
    }
}

void View::completeTodos() const {
    this->viewTodos(new task::Done{});
    this->viewTodos(new task::Rejected{});
}

void View::outstandingTodos() const {
    this->viewTodos(new task::Urgent{});
    this->viewTodos(new task::Normal{});
    this->viewTodos(new task::Low{});
}

void View::doneTodos() const { this->viewTodos(new task::Done{}); }

void View::lowTodos() const { this->viewTodos(new task::Low{}); }

void View::normalTodos() const { this->viewTodos(new task::Normal{}); }

void View::rejectTodos() const { this->viewTodos(new task::Rejected{}); }

void View::urgentTodos() const { this->viewTodos(new task::Urgent{}); }

/* Private methods */
void View::viewTodos(task::TaskTypeAbstract *const taskType) const {
    if (taskType == NULL) {
        throw std::logic_error{"NULL passed to viewTodos method"};
    }
    taskType->view();
}

} // namespace action
