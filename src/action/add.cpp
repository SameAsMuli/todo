#include <chrono> // std::chrono

#include "action/add.hpp"
#include "error/duplicate_task.hpp"
#include "error/empty_argument.hpp"
#include "error/incompatible_options.hpp"
#include "file/definitions.hpp"
#include "file/tasks_data.hpp"
#include "input/option.hpp"
#include "util/fs.hpp"
#include "util/string.hpp"

namespace {

std::string construct_action_name(const todo::task::Type type) {
    switch (type) {
    case todo::task::Type::normal:
        return "add";
    default:
        return type.to_string();
    }
}

} // namespace

namespace todo {
namespace action {

Add::Add(const task::Type taskType)
    : ActionAbstract(construct_action_name(taskType),
                     "Add " + taskType.to_string() + " priority TODO"),
      m_taskType(taskType) {
    /* Define the valid options for this action */
    this->add_valid_option(input::Option::global);
    this->add_valid_option(input::Option::local);

    if (taskType.is_complete()) {
        throw std::logic_error{"non-complete type '" + taskType.to_string() +
                               "' used for an add action"};
    }

    /* Define any aliases for this option */
    switch (taskType) {
    case todo::task::Type::normal:
        this->add_alias("normal");
        break;
    default:
        break;
    }
}

void Add::run(const input::Input &input) {
    /* Check we have a valid input */
    auto description = input.get_action_arg_string();
    util::string::trim(description);
    if (description.empty()) {
        throw todo::error::EmptyArgument{"add method"};
    }

    /* Sense check the options */
    auto local = input.has_option(input::Option::local);
    auto global = input.has_option(input::Option::global);

    if (local && global) {
        throw todo::error::IncompatibleOptions(input::Option::local,
                                               input::Option::global);
    }

    /* Create a local todo director if needed */
    if (local) {
        util::fs::init_dir(todo::file::get_local_todo_dir_name());
    }

    /* Read the tasks file for the chosen directory */
    auto tasks = todo::file::TasksData{todo::file::File::tasks, global};

    /* Check that the task doesn't already exist */
    auto matchingTasks = tasks.search([description](const auto &task) {
        return task.get_description() == description;
    });

    if (matchingTasks.size() > 0) {
        for (auto const &task : matchingTasks) {
            if (!task.get_type().is_complete()) {
                throw todo::error::DuplicateTask();
            }
        }
    }

    /* Create and populate a task to be added */
    todo::task::Task task{this->get_task_type(), description};
    task.set_time_added(std::chrono::system_clock::now());
    tasks.add_task(task);

    /* Write changes to file */
    tasks.write();
}

std::string Add::usage() const {
    return "usage: todo " + this->get_name() + " <task description>";
}

std::string Add::description() const {
    return "Add a new, " + this->get_task_type().to_string() +
           " priority TODO to the specified TODO directory. If the " +
           input::Option(input::Option::local).to_string() +
           " option is specified then the current directory will be used, "
           "even if it does not already contain TODO information.\n\n"
           "If a TODO with the same description already exists within the "
           "specified TODO directory then a duplicate will not be created.";
}

} // namespace action
} // namespace todo
