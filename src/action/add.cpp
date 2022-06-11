#include <chrono>    // std::chrono
#include <fstream>   // std::ofstream
#include <ostream>   // std::endl
#include <stdexcept> // std::runtime_error

#include "action/add.hpp"
#include "error/duplicate_task.hpp"
#include "error/empty_argument.hpp"
#include "error/incompatible_options.hpp"
#include "file/accessors.hpp"
#include "file/definitions.hpp"
#include "file/mutators.hpp"
#include "input/input.hpp"
#include "input/option.hpp"
#include "task/outstanding_abstract.hpp"
#include "util/fs.hpp"
#include "util/string.hpp"

namespace {

void addCompleteTask(const todo::task::Type type, const input::Input &input) {
    bool global = input.hasOption(input::Option::global);

    /* Make sure we can open the complete file */
    std::ofstream ofs{type.getFile(global).string(), std::ios_base::app};
    if (!ofs.is_open()) {
        throw std::runtime_error{"Unable to open TODO file"};
    }

    /* Find the tasks that match the search string and remove them */
    auto tasks = todo::file::removeTasks(input.getActionArgString(),
                                         todo::file::getOutstanding(global),
                                         input.hasOption(input::Option::force),
                                         input.hasOption(input::Option::exact));

    for (auto &task : tasks) {
        /* Update found task with the previous time and the previous type */
        task.setPreviousType(task.getType());
        task.setPreviousTimeAdded(task.getTimeAdded());
        task.setType(type);
        task.setTimeAdded(std::chrono::system_clock::now());

        /* Write the task to the complete file */
        ofs << task << std::endl;
    }
}

void addOutstandingTask(const todo::task::Type type,
                        const input::Input &input) {
    /* Check we have a valid input */
    auto description = input.getActionArgString();
    util::string::trim(description);
    if (description.empty()) {
        throw todo::error::EmptyArgument{"add method"};
    }

    /* Sense check the options */
    if (input.hasOption(input::Option::local) &&
        input.hasOption(input::Option::global)) {
        throw todo::error::IncompatibleOptions(input::Option::local,
                                               input::Option::global);
    }

    /* Create a local todo file if needed */
    if (input.hasOption(input::Option::local)) {
        auto dir = util::fs::CurrentDir();
        if (dir != todo::file::getTodoDir(false)) {
            todo::file::initialise(false);
        }
    }

    /* Check that the task doesn't already exist */
    auto [match, others] = todo::file::search(
        description, type.getFile(input.hasOption(input::Option::global)),
        true);

    if (match.size() > 0) {
        throw todo::error::DuplicateTask();
    }

    /* Create and populate a task to be added */
    todo::task::Task task{type, description};
    task.setTimeAdded(std::chrono::system_clock::now());

    std::ofstream ofs{
        type.getFile(input.hasOption(input::Option::global)).string(),
        std::ios_base::app};
    if (ofs.is_open()) {
        ofs << task << std::endl;
    } else {
        throw std::runtime_error{"Unable to open TODO file"};
    }
}

std::string constructActionName(const todo::task::Type type) {
    switch (type) {
    case todo::task::Type::normal:
        return "add";
    case todo::task::Type::rejected:
        return "reject";
    default:
        return type.toString();
    }
}

std::string constructAddCompleteDescription(const todo::task::Type type) {
    return "Mark any outstanding TODOs as " + type.toString() +
           " if they match the given input. The TODO will then be "
           "considered as complete.\n\n"
           "By default, the action will match any TODO which is a superset "
           "of the given input, but will only allow a single TODO to be "
           "marked as " +
           type.toString() +
           "at a time.\n\n"
           "To mark all matched TODOs as " +
           type.toString() + ", use the " +
           input::Option(input::Option::force).toString() +
           " option. Use the " +
           input::Option(input::Option::exact).toString() +
           " option to only match TODOs that have the same description as "
           "the input, and not match against superset TODOs.";
}

std::string constructAddOutstandingDescription(const todo::task::Type type) {
    return "Add a new, " + type.toString() +
           " priority TODO to the specified TODO directory. If the " +
           input::Option(input::Option::local).toString() +
           " option is specified then the current directory will be used, "
           "even if it does not already contain TODO information.\n\n"
           "If a TODO with the same description already exists within the "
           "specified TODO directory then a duplicate will not be created.";
}

std::string constructHelpText(const todo::task::Type type) {
    if (type.isComplete())
        return "Mark a TODO as " + type.toString();
    else
        return "Add " + type.toString() + " priority TODO";
}

} // namespace

namespace todo {
namespace action {

Add::Add(const task::Type taskType)
    : ActionAbstract(constructActionName(taskType),
                     constructHelpText(taskType)),
      m_taskType(taskType) {
    /* Define the valid options for this action */
    this->addValidOption(input::Option::global);

    if (taskType.isComplete()) {
        this->addValidOption(input::Option::exact);
        this->addValidOption(input::Option::force);
    } else {
        this->addValidOption(input::Option::local);
    }

    /* Define any aliases for this option */
    switch (taskType) {
    case todo::task::Type::normal:
        this->addAlias("normal");
        break;
    default:
        break;
    }
}

void Add::run(const input::Input &input) {
    if (this->getTaskType().isComplete())
        addCompleteTask(this->getTaskType(), input);
    else
        addOutstandingTask(this->getTaskType(), input);
}

std::string Add::usage() const {
    return "usage: todo " + this->getName() + " [<task description>]";
}

std::string Add::description() const {
    if (this->getTaskType().isComplete())
        return constructAddCompleteDescription(this->getTaskType());
    else
        return constructAddOutstandingDescription(this->getTaskType());
}

} // namespace action
} // namespace todo
