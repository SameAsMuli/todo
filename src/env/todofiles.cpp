#include <fstream> // std::ofstream
#include <string>  // std::string

#include "env/todofiles.hpp"
#include "util/fs.hpp"
#include "util/xdg.hpp"

void TodoFiles::initialise()
{
    if (util::fs::HomeDir().empty()) {
        throw std::runtime_error("Unable to find HOME directory.");
    }

    TodoFiles::initialiseFile(TodoFiles::getOutstanding());
    TodoFiles::initialiseFile(TodoFiles::getComplete());
}

fs::path TodoFiles::getOutstanding()
{
    return TodoFiles::getTodoDir() / "outstanding_tasks";
}

fs::path TodoFiles::getComplete()
{
    return TodoFiles::getTodoDir() / "complete_tasks";
}

fs::path TodoFiles::getTemp()
{
    return TodoFiles::getTodoDir() / "temp";
}


// Private methods
fs::path TodoFiles::getTodoDir()
{
    return util::xdg::configHome() / "todo";
}

void TodoFiles::initialiseFile(const fs::path& file)
{
    // Create parent directory if it doesn't already exist
    fs::create_directories(file.parent_path());

    // Create file if it doesn't already exist
    if (!fs::exists(file)) {
        std::ofstream(file.string()); // create file
    }
}
