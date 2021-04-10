#include <chrono>    // std::chrono
#include <fstream>   // std::ofstream
#include <ostream>   // std::endl
#include <stdexcept> // std::runtime_error

#include "error/empty_argument.hpp"
#include "error/incompatible_options.hpp"
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
    auto description = input.getActionArgString();
    if (description.empty()) {
        throw error::EmptyArgument{"add method"};
    }

    if (input.hasOption(input::Option::local) &&
        input.hasOption(input::Option::global)) {
        throw error::IncompatibleOptions(input::Option::local,
                                         input::Option::global);
    }

    if (input.hasOption(input::Option::local)) {
        auto dir = util::fs::CurrentDir();
        if (dir != todo::file::getTodoDir(false)) {
            todo::file::initialise(false);
        }
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
