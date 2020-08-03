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

    TodoFiles::initialiseFile(TodoFiles::getArchive());
    TodoFiles::initialiseFile(TodoFiles::getLow());
    TodoFiles::initialiseFile(TodoFiles::getNormal());
    TodoFiles::initialiseFile(TodoFiles::getUrgent());
}

fs::path TodoFiles::getArchive()
{
    return TodoFiles::getTodoDir() / "archive";
}

fs::path TodoFiles::getLow()
{
    return TodoFiles::getTodoDir() / "low";
}

fs::path TodoFiles::getNormal()
{
    return TodoFiles::getTodoDir() / "normal";
}

fs::path TodoFiles::getUrgent()
{
    return TodoFiles::getTodoDir() / "urgent";
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
