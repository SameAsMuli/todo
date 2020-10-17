#include <chrono>     // std::chrono
#include <filesystem> // std::filesystem
#include <fstream>    // std::ofstream
#include <stdexcept>  // std::runtime_error
#include <string>     // std::string

#include "error/inspecific_task.hpp"
#include "error/unknown_task.hpp"
#include "file/accessors.hpp"
#include "file/definitions.hpp"
#include "file/mutators.hpp"
#include "task/metadata.hpp"
#include "util/fs.hpp"

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
namespace file {

void initialise() {
    if (util::fs::HomeDir().empty()) {
        throw std::runtime_error("Unable to find HOME directory.");
    }

    initialiseFile(getOutstanding());
    initialiseFile(getComplete());
    initialiseFile(getArchive());

    /* Archive any tasks completed more than a day ago */
    archive(1440);
}

task::Task removeTask(const std::string &searchString,
                      const std::filesystem::path &file) {
    /* Search for matching tasks */
    auto [matchingTasks, nonMatchingTasks] = search(searchString, file);

    /* Error if no tasks, or more than one task, matched the search string */
    auto numMatches = matchingTasks.size();
    if (numMatches == 0) {
        throw error::UnknownTask();
    } else if (numMatches > 1) {
        throw error::InspecificTask(numMatches);
    }

    /* Open a temp file */
    std::ofstream tempFile{getTemp().string()};
    if (!tempFile.is_open()) {
        throw std::runtime_error{"Unable to open TODO file"};
    }

    /* Write all non-matching tasks to the temp file */
    for (auto const &task : nonMatchingTasks) {
        tempFile << task << '\n';
    }

    tempFile.close();

    /* Overwrite the given file with the temp file (removes the matched task) */
    if (std::remove(file.string().c_str()) ||
        std::rename(getTemp().string().c_str(), file.string().c_str())) {
        std::perror("Error swapping files");
        throw std::runtime_error{"Unable to update TODO file"};
    }

    /* Only have one match, so return it */
    return matchingTasks.at(0);
}

std::vector<task::Task> removeTasks(const std::string &searchString,
                                    const std::filesystem::path &file) {
    /* Search for matching tasks */
    auto [matchingTasks, nonMatchingTasks] = search(searchString, file);

    /* If no tasks matched just return here */
    if (matchingTasks.size() == 0) {
        return matchingTasks;
    }

    /* Open a temp file */
    std::ofstream tempFile{getTemp().string()};
    if (!tempFile.is_open()) {
        throw std::runtime_error{"Unable to open TODO file"};
    }

    /* Write all non-matching tasks to the temp file */
    for (auto const &task : nonMatchingTasks) {
        tempFile << task << '\n';
    }

    tempFile.close();

    /* Overwrite the given file with the temp file (removes the matched
     * task) */
    if (std::remove(file.string().c_str()) ||
        std::rename(getTemp().string().c_str(), file.string().c_str())) {
        std::perror("Error swapping files");
        throw std::runtime_error{"Unable to update TODO file"};
    }

    return matchingTasks;
}

void archive(unsigned int maxMins) {
    /* Open the archive, complete and temp files */
    std::ofstream archiveFile{getArchive().string(), std::ios_base::app};
    if (!archiveFile.is_open()) {
        throw std::runtime_error{"Unable to open TODO file"};
    }

    std::ifstream completeFile{getComplete().string()};
    if (!completeFile.is_open()) {
        throw std::runtime_error{"Unable to open TODO file"};
    }

    std::ofstream tempFile{getTemp().string()};
    if (!tempFile.is_open()) {
        throw std::runtime_error{"Unable to open TODO file"};
    }

    /* Attempt to find tasks older than the given number of minutes */
    std::vector<task::Task> matchingTasks;
    std::chrono::system_clock::time_point now =
        std::chrono::system_clock::now();

    task::Task task;
    while (completeFile >> task) {
        auto ageMins = std::chrono::duration_cast<std::chrono::minutes>(
                           now - task.getMetadata().getTimeAdded())
                           .count();

        if (maxMins <= ageMins) {
            archiveFile << task << '\n';
        } else {
            tempFile << task << '\n';
        }
    }

    archiveFile.close();
    completeFile.close();
    tempFile.close();

    /* Overwrite the complete file with the temp file */
    if (std::remove(getComplete().string().c_str()) ||
        std::rename(getTemp().string().c_str(),
                    getComplete().string().c_str())) {
        std::perror("Error swapping files");
        throw std::runtime_error{"Unable to update TODO file"};
    }
}

} // namespace file
} // namespace todo