#include <chrono>    // std::chrono
#include <fstream>   // std::ofstream
#include <stdexcept> // std::runtime_error

#include "action/undo.hpp"
#include "error/inspecific_task.hpp"
#include "error/unknown_task.hpp"
#include "file/tasks_data.hpp"

namespace todo {
namespace action {

Undo::Undo() : ActionAbstract("undo", "Unmark a TODO as completed") {
    this->addAlias("revert");
    this->addValidOption(input::Option::exact);
    this->addValidOption(input::Option::force);
    this->addValidOption(input::Option::global);
}

std::string Undo::description() const {
    return "Revert any complete TODOs that match the given input back to "
           "outstanding TODOs. TODOs will revert to their original priority "
           "level.\n\n"
           "By default, the action will match any TODO which is a superset of "
           "the given input, but will only allow a single TODO to be undone "
           "at a time.\n\n"
           "To remove all matched TODOs, use the " +
           input::Option(input::Option::force).toString() +
           " option. Use the " +
           input::Option(input::Option::exact).toString() +
           " option to only match TODOs that have the same description as the "
           "input, and not match against superset TODOs.";
}

std::string Undo::usage() const {
    return "usage: todo " + this->getName() + " <task description>";
}

void Undo::run(const input::Input &input) {
    /* Open the tasks file */
    auto tasks = file::TasksData{file::File::tasks,
                                 input.hasOption(input::Option::global)};

    /* Find all matching tasks and revert them */
    auto exact = input.hasOption(input::Option::exact);
    auto searchString = input.getActionArgString();
    unsigned int matches = 0;

    tasks.forEach([exact, &matches, searchString](auto &task) {
        if (exact ? task.getDescription() == searchString
                  : task.getDescription().find(searchString) !=
                        std::string::npos) {
            task.setType(task.getPreviousType());
            task.setTimeAdded(task.getPreviousTimeAdded());
            task.setPreviousType(task::Type::UNKNOWN_TYPE);
            matches++;
        }
    });

    /* If we aren't using force, check we affected exactly one task */
    if (input.hasOption(input::Option::force)) {
        if (matches == 0) {
            throw error::UnknownTask{};
        }
        if (matches > 1) {
            throw error::InspecificTask{matches};
        }
    }

    /* Write changes to file */
    tasks.write();
}

} // namespace action
} // namespace todo
