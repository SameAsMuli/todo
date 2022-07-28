#ifndef TODO_FILE_DEFINITIONS_H
#define TODO_FILE_DEFINITIONS_H

#include <filesystem> // std::filesystem

namespace todo {
namespace file {

/**
 * @brief Return the name used for the top level of local todo directories.
 *
 * @return A filesystem path with the name used for each local todo directory.
 */
std::filesystem::path getLocalTodoDirName();

/**
 * @brief Get the directory containing all todo-related files.
 *
 * If global is set to false, then the function will search the current
 * directory, followed by each successive parent directory, until either a todo
 * directory is found or the home directory is reached.
 *
 * If no todo directory is found before or in the home directory, or global is
 * set to true, then this function will return a path to "<configHome>/todo"
 * where "<configHome>" is the value returned by util::xdg::configHome.
 *
 * @param global Whether to return the global or local todo directory.
 *
 * @return A filesystem path to the directory containing all todo files.
 */
std::filesystem::path getTodoDir(bool global);

} // namespace file
} // namespace todo

#endif
