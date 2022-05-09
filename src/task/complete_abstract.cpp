#include <chrono>    // std::chrono
#include <fstream>   // std::ofstream
#include <stdexcept> // std::runtime_error

#include "file/definitions.hpp"
#include "file/mutators.hpp"
#include "input/option.hpp"
#include "task/complete_abstract.hpp"

namespace todo {
namespace task {

CompleteAbstract::CompleteAbstract(const std::string &name, const Type &type)
    : TaskTypeAbstract(file::getComplete, name, type) {}

void CompleteAbstract::add(const input::Input &input) {
    bool global = input.hasOption(input::Option::global);

    /* Make sure we can open the complete file */
    std::ofstream ofs{this->getFile(global).string(), std::ios_base::app};
    if (!ofs.is_open()) {
        throw std::runtime_error{"Unable to open TODO file"};
    }

    /* Find the tasks that match the search string and remove them */
    auto tasks = file::removeTasks(input.getActionArgString(),
                                   file::getOutstanding(global),
                                   input.hasOption(input::Option::force),
                                   input.hasOption(input::Option::exact));

    for (auto &task : tasks) {
        /* Update found task with the previous time and the previous type */
        task.setPreviousType(task.getType());
        task.setPreviousTimeAdded(task.getTimeAdded());
        task.setType(this->getType());
        task.setTimeAdded(std::chrono::system_clock::now());

        /* Write the task to the complete file */
        ofs << task << std::endl;
    }
}

void CompleteAbstract::undo(const input::Input &input) {
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
        task.setPreviousType(Type::UNKNOWN_TYPE);

        /* Write the task to the outstanding file */
        ofs << task << std::endl;
    }
}

} // namespace task
} // namespace todo
