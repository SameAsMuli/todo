#include <chrono>    // std::chrono
#include <cstdio>    // std::remove
#include <fstream>   // std::ofstream
#include <stdexcept> // std::runtime_error

#include "error/empty_argument.hpp"
#include "file/definitions.hpp"
#include "file/mutators.hpp"
#include "input/input.hpp"
#include "input/option_type.hpp"
#include "task/complete_abstract.hpp"
#include "task/metadata.hpp"
#include "task/prefix.hpp"
#include "task/task.hpp"

namespace todo {
namespace task {

CompleteAbstract::CompleteAbstract(const std::string &name,
                                   const Prefix &prefix)
    : TaskTypeAbstract(file::getComplete, name, prefix) {}

void CompleteAbstract::add(const input::Input &input) {
    bool global = input.hasOption(input::OptionType::global);

    /* Make sure we can open the complete file */
    std::ofstream ofs{this->getFile(global).string(), std::ios_base::app};
    if (!ofs.is_open()) {
        throw std::runtime_error{"Unable to open TODO file"};
    }

    /* Find the task that matches the search string and remove it */
    auto task = file::removeTask(input.getActionArgString(),
                                 file::getOutstanding(global));

    /* Update the found task with the current time and the previous prefix */
    Metadata metadata = task.getMetadata();
    metadata.setPreviousTimeAdded(task.getMetadata().getTimeAdded());
    metadata.setTimeAdded(std::chrono::system_clock::now());
    metadata.setPreviousPrefix(task.getPrefix());

    task.setPrefix(this->getPrefix());
    task.setMetadata(metadata);

    /* Write the task to the complete file */
    ofs << task << std::endl;
}

void CompleteAbstract::undo(const input::Input &input) {
    /* Check the input */
    if (input.getActionArgCount() == 0) {
        throw error::EmptyArgument{"undo"};
    }

    bool global = input.hasOption(input::OptionType::global);

    /* Make sure we can open the outstanding file */
    std::ofstream ofs{file::getOutstanding(global).string(),
                      std::ios_base::app};
    if (!ofs.is_open()) {
        throw std::runtime_error{"Unable to open TODO file"};
    }

    /* Find the task that matches the search string and remove it */
    auto task =
        file::removeTask(input.getActionArgString(), file::getComplete(global));

    /* Update the found task with the previous time and the previous prefix */
    Metadata metadata = task.getMetadata();
    metadata.setTimeAdded(task.getMetadata().getPreviousTimeAdded());
    metadata.setPreviousPrefix(Prefix::NULL_PREFIX);

    task.setPrefix(task.getMetadata().getPreviousPrefix());
    task.setMetadata(metadata);

    /* Write the task to the outstanding file */
    ofs << task << std::endl;
}

} // namespace task
} // namespace todo
