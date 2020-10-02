#include <filesystem> // std::filesystem
#include <fstream>    // std::ofstream
#include <stdexcept>  // std::runtime_error
#include <string>     // std::string

#include "task/metadata.hpp"
#include "todo/files.hpp"
#include "todo/inspecific_task.hpp"
#include "todo/unknown_task.hpp"
#include "util/fs.hpp"
#include "util/xdg.hpp"

namespace {

/**
 * @brief Create a given file and its parent directories if necessary.
 *
 * @param file The filesystem path to create.
 */
void initialiseFile(const std::filesystem::path &file) {
    /* Create parent directory if it doesn't already exist */
    std::filesystem::create_directories(file.parent_path());

    /* Create file if it doesn't already exist */
    if (!std::filesystem::exists(file)) {
        std::ofstream(file.string());
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

std::pair<std::vector<task::Task>, std::vector<task::Task>>
search(const std::string &searchString, const std::filesystem::path &file) {
    /* Check the seach string */
    if (searchString.empty()) {
        throw std::logic_error{"Empty input passed to add method"};
    }

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

task::Task removeTask(const std::string &searchString,
                      const std::filesystem::path &file) {
    /* Search for matching tasks */
    auto [matchingTasks, nonMatchingTasks] = search(searchString, file);

    /* Error if no tasks, or more than one task, matched the search string */
    auto numMatches = matchingTasks.size();
    if (numMatches == 0) {
        throw todo::UnknownTask();
    } else if (numMatches > 1) {
        throw todo::InspecificTask(numMatches);
    }

    /* Open a temp file */
    std::ofstream tempFile{todo::files::getTemp().string()};
    if (!tempFile.is_open()) {
        throw std::runtime_error{"Unable to open TODO file"};
    }

    /* Write all non-matching tasks to the temp file */
    for (auto const &task : nonMatchingTasks) {
        tempFile << task << '\n';
    }

    /* Overwrite the given file with the temp file (removes the matched task) */
    if (std::remove(file.string().c_str()) ||
        std::rename(todo::files::getTemp().string().c_str(),
                    file.string().c_str())) {
        std::perror("Error swapping files");
        throw std::runtime_error{"Unable to update TODO file"};
    }

    /* Only have one match, so return it */
    return matchingTasks.at(0);
}

} // namespace files
} // namespace todo
