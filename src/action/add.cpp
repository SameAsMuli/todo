#include <chrono> // std::chrono

#include "action/add.hpp"
#include "error/duplicate_task.hpp"
#include "error/empty_argument.hpp"
#include "error/incompatible_options.hpp"
#include "error/inspecific_task.hpp"
#include "error/unknown_task.hpp"
#include "file/definitions.hpp"
#include "file/tasks_data.hpp"
#include "input/option.hpp"
#include "util/fs.hpp"
#include "util/string.hpp"

namespace {

void addCompleteTask(const todo::task::Type type, const input::Input &input) {
    /* Open the tasks file */
    auto tasks = todo::file::TasksData{todo::file::File::tasks,
                                       input.hasOption(input::Option::global)};

    /* Find all matching tasks and set them as complete */
    auto exact = input.hasOption(input::Option::exact);
    auto searchString = input.getActionArgString();
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

void addOutstandingTask(const todo::task::Type type,
                        const input::Input &input) {
    /* Check we have a valid input */
    auto description = input.getActionArgString();
    util::string::trim(description);
    if (description.empty()) {
        throw todo::error::EmptyArgument{"add method"};
    }

    /* Sense check the options */
    auto local = input.hasOption(input::Option::local);
    auto global = input.hasOption(input::Option::global);

    if (local && global) {
        throw todo::error::IncompatibleOptions(input::Option::local,
                                               input::Option::global);
    }

    /* Create a local todo director if needed */
    if (local) {
        util::fs::initDir(todo::file::getLocalTodoDirName());
    }

    /* Read the tasks file for the chosen directory */
    auto tasks = todo::file::TasksData{todo::file::File::tasks, global};

    /* Check that the task doesn't already exist */
    auto matchingTasks = tasks.search([description](const auto &task) {
        return task.getDescription() == description;
    });

    if (matchingTasks.size() > 0) {
        for (auto const &task : matchingTasks) {
            if (!task.getType().isComplete()) {
                throw todo::error::DuplicateTask();
            }
        }
    }

    /* Create and populate a task to be added */
    todo::task::Task task{type, description};
    task.setTimeAdded(std::chrono::system_clock::now());
    tasks.addTask(task);

    /* Write changes to file */
    tasks.write();
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
    return "usage: todo " + this->getName() + " <task description>";
}

std::string Add::description() const {
    if (this->getTaskType().isComplete())
        return constructAddCompleteDescription(this->getTaskType());
    else
        return constructAddOutstandingDescription(this->getTaskType());
}

} // namespace action
} // namespace todo
