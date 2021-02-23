#include <chrono>    // std::chrono
#include <fstream>   // std::ofstream
#include <ostream>   // std::endl
#include <stdexcept> // std::runtime_error

#include "file/definitions.hpp"
#include "task/metadata.hpp"
#include "task/outstanding_abstract.hpp"

namespace todo {
namespace task {

OutstandingAbstract::OutstandingAbstract(const std::string &name,
                                         const Prefix &prefix)
    : TaskTypeAbstract(file::getOutstanding(), name, prefix) {}

void OutstandingAbstract::add(const util::Input &input) {
    auto description = input.toString(util::Input::PARAM_START_INDEX);
    if (description.empty()) {
        throw std::logic_error{"Empty input passed to add method"};
    }

    /* Create and populate a task to be added */
    Metadata metadata;
    metadata.setTimeAdded(std::chrono::system_clock::now());

    Task task{this->getPrefix(), description};
    task.setMetadata(metadata);

    std::ofstream ofs{this->getFile().string(), std::ios_base::app};
    if (ofs.is_open()) {
        ofs << task << std::endl;
    } else {
        throw std::runtime_error{"Unable to open TODO file"};
    }
}

} // namespace task
} // namespace todo
