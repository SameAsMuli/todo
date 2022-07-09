#ifndef TODO_FILES_H
#define TODO_FILES_H

#include <filesystem> // std::filesystem
#include <tuple>      // std::tuple
#include <vector>     // std::vector

#include "task/task.hpp"

namespace todo {
namespace file {

/**
 * @brief Create the applications data files if necessary.
 *
 * Will create the files "archive", "complete_tasks" and "outstanding_tasks" in
 * the chosen todo directory, if they do not already exist.
 *
 * If the global flag is set to true then XDG_CONFIG_DIR will be used, otherwise
 * the directory ".todo" inside the current working directory is used.
 *
 * @param global Whether to use the current working, or global todo, directory.
 */
void initialise(bool global);

/**
 * @brief Search a given data file and remove all tasks matching searchString.
 *
 * Look for tasks in the given data file that match a given substring. Once
 * found, remove the tasks.
 *
 * Unlike removeTask, no exception is thrown if no tasks or multiple tasks are
 * matched. Any file access problems will still throw an error.
 *
 * @param searchString The substring to search for.
 * @param file The data file to search through.
 * @param multipleTasks If false, must match exactly one task or throw an error.
 * @param exactMatch If true, searchString must match whole task description.
 *
 * @return A vector of the removed tasks.
 */
std::vector<task::Task> removeTasks(const std::string &searchString,
                                    const std::filesystem::path &file,
                                    bool multipleTasks = false,
                                    bool exactMatch = false);

/**
 * @brief Move all completed tasks older than numMins to the archive data file.
 *
 * @param numMins Maximum number of minutes until a complete task gets archived.
 * @param global Whether to consider local or global only tasks.
 */
void archive(unsigned int maxMins, bool global = false);

} // namespace file
} // namespace todo

#endif
