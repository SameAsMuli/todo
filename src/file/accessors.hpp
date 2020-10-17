#ifndef TODO_FILE_ACCESSORS_H
#define TODO_FILE_ACCESSORS_H

#include <filesystem> // std::filesystem
#include <tuple>      // std::tuple
#include <vector>     // std::vector

#include "task/task.hpp"

namespace todo {
namespace file {

/**
 * @brief Search a given data file and return tasks matching searchString.
 *
 * Loop all tasks in the given file and add them to one of two vectors based on
 * whether they match the search string or not. An empty searchString will match
 * every task.
 *
 * @param searchString The substring to search for.
 * @param file The data file to search through.
 *
 * @return A pair of vectors for matched and unmatched tasks.
 */
std::pair<std::vector<task::Task>, std::vector<task::Task>>
search(const std::string &searchString, const std::filesystem::path &file);

} // namespace file
} // namespace todo

#endif
