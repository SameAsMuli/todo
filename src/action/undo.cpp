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
    this->add_alias("revert");
    this->add_valid_option(input::Option::exact);
    this->add_valid_option(input::Option::force);
    this->add_valid_option(input::Option::global);
}

std::string Undo::description() const {
    return "Revert any complete TODOs that match the given input back to "
           "outstanding TODOs. TODOs will revert to their original priority "
           "level.\n\n"
           "By default, the action will match any TODO which is a superset of "
           "the given input, but will only allow a single TODO to be undone "
           "at a time.\n\n"
           "To remove all matched TODOs, use the " +
           input::Option(input::Option::force).to_string() +
           " option. Use the " +
           input::Option(input::Option::exact).to_string() +
           " option to only match TODOs that have the same description as the "
           "input, and not match against superset TODOs.";
}

std::string Undo::usage() const {
    return "usage: todo " + this->get_name() + " <task description>";
}

void Undo::run(const input::Input &input) {
    /* Open the tasks file */
    auto tasks = file::TasksData{
        file::File::tasks,
        file::get_todo_dir(input.has_option(input::Option::global))};

    /* Find all matching tasks and revert them */
    auto exact = input.has_option(input::Option::exact);
    auto searchString = input.get_action_arg_string();
    unsigned int matches = 0;

    tasks.for_each([exact, &matches, searchString](task::Task &task) {
        if (exact ? task.get_description() == searchString
                  : task.get_description().find(searchString) !=
                        std::string::npos) {
            task.set_type(task.get_previous_type());
            task.set_time_added(task.get_previous_time_added());
            task.set_previous_type(task::Type::UNKNOWN_TYPE);
            matches++;
        }
    });

    /* If we aren't using force, check we affected exactly one task */
    if (input.has_option(input::Option::force)) {
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
