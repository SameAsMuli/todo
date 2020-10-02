#ifndef TODO_FILES_H
#define TODO_FILES_H

#include <filesystem> // std::filesystem
#include <tuple>      // std::tuple
#include <vector>     // std::vector

#include "task/task.hpp"

namespace todo {
namespace files {

/**
 * @brief Create the applications data files if necessary.
 *
 * Will create the files "outstanding_tasks" and "complete_tasks" in the
 * XDG_CONFIG_DIR, if they do not already exist.
 */
void initialise();

/**
 * @brief Get the "outstanding_tasks" data file.
 *
 * @return A filesystem path to the data file.
 */
std::filesystem::path getOutstanding();

/**
 * @brief Get the "complete_tasks" data file.
 *
 * @return A filesystem path to the data file.
 */
std::filesystem::path getComplete();

/**
 * @brief Get the "temp" data file.
 *
 * This is used for copying between outstanding and complete data files to make
 * sure there is no accidental data loss.
 *
 * @return A filesystem path to the data file.
 */
std::filesystem::path getTemp();

/**
 * @brief Get the directory containing the todo data files.
 *
 * @return A filesystem path to the directory containing the data files.
 */
std::filesystem::path getTodoDir();

/**
 * @brief Search a given data file and return tasks matching searchString.
 *
 * Loop all tasks in the given file and add them to one of two vectors based on
 * whether they match the search string or not.
 *
 * @param searchString The substring to search for.
 * @param file The data file to search through.
 *
 * @return A pair of vectors for matched and unmatched tasks.
 */
std::pair<std::vector<task::Task>, std::vector<task::Task>>
search(const std::string &searchString, const std::filesystem::path &file);

/**
 * @brief Search a given data file and remove the task matching searchString.
 *
 * Look for a task in the given data file that matches a given substring. Once
 * found, remove the task.
 *
 * An exception is thrown if no task is matched or more than one task is
 * matched. Any file access problems will also throw an error.
 *
 * @param searchString The substring to search for.
 * @param file The data file to search through.
 *
 * @return The removed task.
 */
task::Task removeTask(const std::string &searchString,
                      const std::filesystem::path &file);

} // namespace files
} // namespace todo

#endif
