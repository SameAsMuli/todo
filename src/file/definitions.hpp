#ifndef TODO_FILE_DEFINITIONS_H
#define TODO_FILE_DEFINITIONS_H

#include <filesystem> // std::filesystem

namespace todo {
namespace file {

/**
 * @brief Get the "outstanding_tasks" data file.
 *
 * @param global Whether to consider local or global only tasks.
 *
 * @return A filesystem path to the data file.
 */
std::filesystem::path getOutstanding(bool global = false);

/**
 * @brief Get the "complete_tasks" data file.
 *
 * @param global Whether to consider local or global only tasks.
 *
 * @return A filesystem path to the data file.
 */
std::filesystem::path getComplete(bool global = false);

/**
 * @brief Get the "archive" data file.
 *
 * @param global Whether to consider local or global only tasks.
 *
 * Completed tasks can be manually or automatically archived to this file.
 *
 * @return A filesystem path to the data file.
 */
std::filesystem::path getArchive(bool global = false);

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
 * If global is set to false, then the function will search the current
 * directory, followed by each successive parent directory, until either a todo
 * directory is found or the home directory is reached.
 *
 * If no todo directory is found before or in the home directory, or global is
 * set to true, then this function will return a path to "<configHome>/todo"
 * where "<configHome>" is the value returned by util::xdg::configHome.
 *
 * @param global Whether to only return the global todo directory.
 *
 * @return A filesystem path to the directory containing the data files.
 */
std::filesystem::path getTodoDir(bool global);

} // namespace file
} // namespace todo

#endif
