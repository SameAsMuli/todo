#include <cstdlib> // std::getenv
#include <fstream> // std::ofstream
#include <string>  // std::string

#include "env/todofiles.hpp"

void TodoFiles::initialise()
{
    // TODO Use XDG Base Directory Specification
    if (!std::getenv("HOME")) {
        throw std::runtime_error("$HOME is not defined");
    }

    TodoFiles::initialiseFile(TodoFiles::getArchive());
    TodoFiles::initialiseFile(TodoFiles::getLow());
    TodoFiles::initialiseFile(TodoFiles::getNormal());
    TodoFiles::initialiseFile(TodoFiles::getUrgent());
}

fs::path TodoFiles::getArchive()
{
    std::string homeDir = std::getenv("HOME");
    std::string todoDir = homeDir + "/.config/todo";

    return fs::path{todoDir + "/archive"};
}

fs::path TodoFiles::getLow()
{
    std::string homeDir = std::getenv("HOME");
    std::string todoDir = homeDir + "/.config/todo";

    return fs::path{todoDir + "/low"};
}

fs::path TodoFiles::getNormal()
{
    std::string homeDir = std::getenv("HOME");
    std::string todoDir = homeDir + "/.config/todo";

    return fs::path{todoDir + "/normal"};
}

fs::path TodoFiles::getUrgent()
{
    std::string homeDir = std::getenv("HOME");
    std::string todoDir = homeDir + "/.config/todo";

    return fs::path{todoDir + "/urgent"};
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
