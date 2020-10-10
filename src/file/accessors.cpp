#include <filesystem> // std::filesystem
#include <fstream>    // std::ifstream
#include <stdexcept>  // std::runtime_error
#include <string>     // std::string

#include "file/accessors.hpp"
#include "task/metadata.hpp"

namespace todo {
namespace file {

std::pair<std::vector<task::Task>, std::vector<task::Task>>
search(const std::string &searchString, const std::filesystem::path &file) {
    /* Open the given file */
    std::ifstream fileStream{file.string()};
    if (!fileStream.is_open()) {
        throw std::runtime_error{"Unable to open TODO file"};
    }

    std::vector<task::Task> matchingTasks;
    std::vector<task::Task> nonMatchingTasks;

    /* Attempt to find tasks that match the search string */
    task::Task task;
    while (fileStream >> task) {
        if (task.getDescription().find(searchString) != std::string::npos) {
            matchingTasks.push_back(task);
        } else {
            nonMatchingTasks.push_back(task);
        }
    }

    return std::pair<std::vector<task::Task>, std::vector<task::Task>>{
        matchingTasks, nonMatchingTasks};
}

} // namespace file
} // namespace todo
