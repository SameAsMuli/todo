#include <filesystem> // std::filesystem
#include <fstream>    // std::ofstream
#include <stdexcept>  // std::runtime_error
#include <string>     // std::string

#include "todo/files.hpp"
#include "util/fs.hpp"
#include "util/xdg.hpp"

namespace {

void initialiseFile(const std::filesystem::path &file) {
    // Create parent directory if it doesn't already exist
    std::filesystem::create_directories(file.parent_path());

    // Create file if it doesn't already exist
    if (!std::filesystem::exists(file)) {
        std::ofstream(file.string()); // create file
    }
}

} // namespace

namespace todo {
namespace files {

void initialise() {
    if (util::fs::HomeDir().empty()) {
        throw std::runtime_error("Unable to find HOME directory.");
    }

    initialiseFile(getOutstanding());
    initialiseFile(getComplete());
}

std::filesystem::path getOutstanding() {
    return getTodoDir() / "outstanding_tasks";
}

std::filesystem::path getComplete() { return getTodoDir() / "complete_tasks"; }

std::filesystem::path getTemp() { return getTodoDir() / "temp"; }

std::filesystem::path getTodoDir() { return util::xdg::configHome() / "todo"; }

} // namespace files
} // namespace todo
