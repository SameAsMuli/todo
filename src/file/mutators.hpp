#ifndef TODO_FILES_H
#define TODO_FILES_H

#include <filesystem> // std::filesystem
#include <tuple>      // std::tuple
#include <vector>     // std::vector

#include "task/task.hpp"

namespace todo {
namespace file {

/**
 * @brief Move all completed tasks older than numMins to the archive data file.
 *
 * @param numMins Maximum number of minutes until a complete task gets archived.
 * @param global Whether to consider local or global only tasks.
 */
void archiveTasks(unsigned int maxMins, bool global = false);

} // namespace file
} // namespace todo

#endif
