#include <chrono>    // std::chrono
#include <cstdio>    // std::perror, std::remove, std::rename
#include <fstream>   // std::ifstream, std::ofstream
#include <stdexcept> // std::runtime_error

#include "error/empty_argument.hpp"
#include "file/definitions.hpp"
#include "file/mutators.hpp"
#include "task/complete_abstract.hpp"
#include "task/metadata.hpp"
#include "task/prefix.hpp"
#include "task/task.hpp"
#include "util/input.hpp"

namespace todo {
namespace task {

CompleteAbstract::CompleteAbstract(Prefix prefix)
    : TaskTypeAbstract(file::getComplete(), prefix) {}

void CompleteAbstract::add(const util::Input &input) {
    /* Make sure we can open the complete file */
    std::ofstream ofs{this->getFile().string(), std::ios_base::app};
    if (!ofs.is_open()) {
        throw std::runtime_error{"Unable to open TODO file"};
    }

    /* Find the task that matches the search string and remove it */
    auto task = file::removeTask(input.toString(util::Input::PARAM_START_INDEX),
                                 file::getOutstanding());

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

void CompleteAbstract::undo(const util::Input &input) {
    /* Check the input */
    if (!input.hasOption(util::Input::PARAM_START_INDEX)) {
        throw error::EmptyArgument{"undo"};
    }

    /* Make sure we can open the outstanding file */
    std::ofstream ofs{file::getOutstanding().string(), std::ios_base::app};
    if (!ofs.is_open()) {
        throw std::runtime_error{"Unable to open TODO file"};
    }

    /* Find the task that matches the search string and remove it */
    auto task = file::removeTask(input.toString(util::Input::PARAM_START_INDEX),
                                 file::getComplete());

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
