#ifndef TODO_FILES_H
#define TODO_FILES_H

#include <filesystem> // std::filesystem

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

} // namespace files
} // namespace todo

#endif
