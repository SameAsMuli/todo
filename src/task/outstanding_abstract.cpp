#include <chrono>    // std::chrono
#include <fstream>   // std::ofstream
#include <ostream>   // std::endl
#include <stdexcept> // std::runtime_error

#include "error/duplicate_task.hpp"
#include "error/empty_argument.hpp"
#include "error/incompatible_options.hpp"
#include "file/accessors.hpp"
#include "file/definitions.hpp"
#include "file/mutators.hpp"
#include "input/option.hpp"
#include "task/metadata.hpp"
#include "task/outstanding_abstract.hpp"
#include "util/fs.hpp"

namespace todo {
namespace task {

OutstandingAbstract::OutstandingAbstract(const std::string &name,
                                         const Prefix &prefix)
    : TaskTypeAbstract(file::getOutstanding, name, prefix) {}

void OutstandingAbstract::add(const input::Input &input) {
    /* Check we have a valid input */
    auto description = input.getActionArgString();
    if (description.empty()) {
        throw error::EmptyArgument{"add method"};
    }

    /* Sense check the options */
    if (input.hasOption(input::Option::local) &&
        input.hasOption(input::Option::global)) {
        throw error::IncompatibleOptions(input::Option::local,
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
    auto [match, others] = file::search(
        description, this->getFile(input.hasOption(input::Option::global)),
        true);

    if (match.size() > 0) {
        throw error::DuplicateTask();
    }

    /* Create and populate a task to be added */
    Metadata metadata;
    metadata.setTimeAdded(std::chrono::system_clock::now());

    Task task{this->getPrefix(), description};
    task.setMetadata(metadata);

    std::ofstream ofs{
        this->getFile(input.hasOption(input::Option::global)).string(),
        std::ios_base::app};
    if (ofs.is_open()) {
        ofs << task << std::endl;
    } else {
        throw std::runtime_error{"Unable to open TODO file"};
    }
}

} // namespace task
} // namespace todo
