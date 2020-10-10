#ifndef TODO_FILE_DEFINITIONS_H
#define TODO_FILE_DEFINITIONS_H

#include <filesystem> // std::filesystem

namespace todo {
namespace file {

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
 * @brief Get the "archive" data file.
 *
 * Completed tasks can be manually or automatically archived to this file.
 *
 * @return A filesystem path to the data file.
 */
std::filesystem::path getArchive();

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

} // namespace file
} // namespace todo

#endif
