#include <chrono> // std::chrono

#include "action/complete.hpp"
#include "error/inspecific_task.hpp"
#include "error/unknown_task.hpp"
#include "file/tasks_data.hpp"

namespace {

std::string constructActionName(const todo::task::Type type) {
    switch (type) {
    case todo::task::Type::rejected:
        return "reject";
    default:
        return type.toString();
    }
}

} // namespace

namespace todo {
namespace action {

Complete::Complete(const task::Type taskType)
    : ActionAbstract(constructActionName(taskType),
                     "Mark a TODO as " + taskType.toString()),
      m_taskType(taskType) {
    /* Define the valid options for this action */
    this->addValidOption(input::Option::global);
    this->addValidOption(input::Option::exact);
    this->addValidOption(input::Option::force);

    if (!taskType.isComplete()) {
        throw std::logic_error{"non-complete type '" + taskType.toString() +
                               "' used for a completion action"};
    }
}

void Complete::run(const input::Input &input) {
    /* Open the tasks file */
    auto tasks = todo::file::TasksData{todo::file::File::tasks,
                                       input.hasOption(input::Option::global)};

    /* Find all matching tasks and set them as complete */
    auto exact = input.hasOption(input::Option::exact);
    auto searchString = input.getActionArgString();
    auto type = this->getTaskType();
    unsigned int matches = 0;

    tasks.forEach([exact, &matches, searchString, type](auto &task) mutable {
        if (exact ? task.getDescription() == searchString
                  : task.getDescription().find(searchString) !=
                        std::string::npos) {
            task.setPreviousType(task.getType());
            task.setPreviousTimeAdded(task.getTimeAdded());
            task.setType(type);
            task.setTimeAdded(std::chrono::system_clock::now());
            matches++;
        }
    });

    /* If we aren't using force, check we affected exactly one task */
    if (!input.hasOption(input::Option::force)) {
        if (matches == 0) {
            throw todo::error::UnknownTask{};
        }
        if (matches > 1) {
            throw todo::error::InspecificTask{matches};
        }
    }

    /* Write changes to file */
    tasks.write();
}

std::string Complete::usage() const {
    return "usage: todo " + this->getName() + " <task description>";
}

std::string Complete::description() const {
    return "Mark any outstanding TODOs as " + this->getTaskType().toString() +
           " if they match the given input. The TODO will then be "
           "considered as complete.\n\n"
           "By default, the action will match any TODO which is a superset "
           "of the given input, but will only allow a single TODO to be "
           "marked as " +
           this->getTaskType().toString() +
           "at a time.\n\n"
           "To mark all matched TODOs as " +
           this->getTaskType().toString() + ", use the " +
           input::Option(input::Option::force).toString() +
           " option. Use the " +
           input::Option(input::Option::exact).toString() +
           " option to only match TODOs that have the same description as "
           "the input, and not match against superset TODOs.";
}

} // namespace action
} // namespace todo
