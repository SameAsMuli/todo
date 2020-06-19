#include <cstdlib> // std::getenv
#include <fstream> // std::ofstream
#include <string>  // std::string

#include "TodoFiles.hpp"

TodoFiles::TodoFiles()
{
    // TODO Use XDG Base Directory Specification
    if (std::getenv("HOME")) {

        std::string homeDir = std::getenv("HOME");
        std::string todoDir = homeDir + "/.config/todo";

        this->m_archive = fs::path{todoDir + "/archive"};
        this->m_low     = fs::path{todoDir + "/low"    };
        this->m_normal  = fs::path{todoDir + "/normal" };
        this->m_urgent  = fs::path{todoDir + "/urgent" };

    } else {
        throw std::runtime_error("$HOME is not defined");
    }

    TodoFiles::initialiseFile(this->m_archive);
    TodoFiles::initialiseFile(this->m_low);
    TodoFiles::initialiseFile(this->m_normal);
    TodoFiles::initialiseFile(this->m_urgent);
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
