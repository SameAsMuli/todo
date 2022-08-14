#include <chrono> // std::chrono

#include "action/complete.hpp"
#include "error/inspecific_task.hpp"
#include "error/unknown_task.hpp"
#include "file/tasks_data.hpp"

namespace {

std::string construct_action_name(const todo::task::Type type) {
    switch (type) {
    case todo::task::Type::rejected:
        return "reject";
    default:
        return type.to_string();
    }
}

} // namespace

namespace todo {
namespace action {

Complete::Complete(const task::Type taskType)
    : ActionAbstract(construct_action_name(taskType),
                     "Mark a TODO as " + taskType.to_string()),
      m_taskType(taskType) {
    /* Define the valid options for this action */
    this->add_valid_option(input::Option::global);
    this->add_valid_option(input::Option::exact);
    this->add_valid_option(input::Option::force);

    if (!taskType.is_complete()) {
        throw std::logic_error{"non-complete type '" + taskType.to_string() +
                               "' used for a completion action"};
    }
}

void Complete::run(const input::Input &input) {
    /* Open the tasks file */
    auto tasks = todo::file::TasksData{todo::file::File::tasks,
                                       input.hasOption(input::Option::global)};

    /* Find all matching tasks and set them as complete */
    auto exact = input.hasOption(input::Option::exact);
    auto searchString = input.get_actionArgString();
    auto type = this->get_task_type();
    unsigned int matches = 0;

    tasks.for_each([exact, &matches, searchString, type](auto &task) mutable {
        if (exact ? task.get_description() == searchString
                  : task.get_description().find(searchString) !=
                        std::string::npos) {
            task.set_previous_type(task.get_type());
            task.set_previous_time_added(task.get_time_added());
            task.set_type(type);
            task.set_time_added(std::chrono::system_clock::now());
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
    return "usage: todo " + this->get_name() + " <task description>";
}

std::string Complete::description() const {
    return "Mark any outstanding TODOs as " +
           this->get_task_type().to_string() +
           " if they match the given input. The TODO will then be "
           "considered as complete.\n\n"
           "By default, the action will match any TODO which is a superset "
           "of the given input, but will only allow a single TODO to be "
           "marked as " +
           this->get_task_type().to_string() +
           "at a time.\n\n"
           "To mark all matched TODOs as " +
           this->get_task_type().to_string() + ", use the " +
           input::Option(input::Option::force).to_string() +
           " option. Use the " +
           input::Option(input::Option::exact).to_string() +
           " option to only match TODOs that have the same description as "
           "the input, and not match against superset TODOs.";
}

} // namespace action
} // namespace todo
