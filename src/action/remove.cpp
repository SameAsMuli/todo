#include "action/remove.hpp"
#include "error/empty_argument.hpp"
#include "error/inspecific_task.hpp"
#include "error/unknown_task.hpp"
#include "file/definitions.hpp"
#include "file/mutators.hpp"
#include "file/tasks_data.hpp"

namespace todo {
namespace action {

Remove::Remove() : ActionAbstract("remove", "Remove an outstanding TODO") {
    this->add_valid_option(input::Option::exact);
    this->add_valid_option(input::Option::force);
    this->add_valid_option(input::Option::global);
}

std::string Remove::description() const {
    return "Remove any outstanding TODOs that match the given input. Complete "
           "TODOs will not be considered for removal.\n\n"
           "By default, the action will match any TODO which is a superset of "
           "the given input, but will only allow a single TODO to be removed "
           "at a time.\n\n"
           "To remove all matched TODOs, use the " +
           input::Option(input::Option::force).to_string() +
           " option. Use the " +
           input::Option(input::Option::exact).to_string() +
           " option to only match TODOs that have the same description as the "
           "input, and not match against superset TODOs.";
}

std::string Remove::usage() const {
    return "usage: todo " + this->get_name() + " <task description>";
}

void Remove::run(const input::Input &input) {
    /* Form and check the seach string */
    auto searchString = input.get_actionArgString();
    if (searchString.empty()) {
        throw error::EmptyArgument{"remove"};
    }

    /* Get options */
    auto exact = input.hasOption(input::Option::exact);
    auto force = input.hasOption(input::Option::force);
    auto global = input.hasOption(input::Option::global);

    /* Read the tasks file */
    auto tasks = file::TasksData{file::File::tasks, global};

    /* Remove matching tasks */
    auto numRemoved = tasks.remove_tasks([exact, searchString](auto &task) {
        if (exact) {
            return task.get_description() == searchString;
        }
        return task.get_description().find(searchString) != std::string::npos;
    });

    /* If we aren't using force, check we affected exactly one task */
    if (!force) {
        if (numRemoved == 0) {
            throw error::UnknownTask{};
        }
        if (numRemoved > 1) {
            throw error::InspecificTask{numRemoved};
        }
    }

    /* Write changes to file */
    tasks.write();
}

} // namespace action
} // namespace todo
