#include <chrono>    // std::chrono
#include <fstream>   // std::ofstream
#include <stdexcept> // std::runtime_error

#include "action/undo.hpp"
#include "file/mutators.hpp"

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

void Undo::run(const input::Input &input) {
    bool global = input.hasOption(input::Option::global);

    /* Make sure we can open the outstanding file */
    std::ofstream ofs{file::getOutstanding(global).string(),
                      std::ios_base::app};
    if (!ofs.is_open()) {
        throw std::runtime_error{"Unable to open TODO file"};
    }

    /* Find the tasks that match the search string and remove them */
    auto tasks =
        file::removeTasks(input.getActionArgString(), file::getComplete(global),
                          input.hasOption(input::Option::force),
                          input.hasOption(input::Option::exact));

    for (auto &task : tasks) {
        /* Update found task with the previous time and the previous type */
        task.setType(task.getPreviousType());
        task.setTimeAdded(task.getPreviousTimeAdded());
        task.setPreviousType(task::Type::UNKNOWN_TYPE);

        /* Write the task to the outstanding file */
        ofs << task << std::endl;
    }
}

} // namespace action
} // namespace todo
