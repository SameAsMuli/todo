#ifndef TODO_FILE_DEFINITIONS_H
#define TODO_FILE_DEFINITIONS_H

#include <filesystem> // std::filesystem

namespace todo {
namespace file {

/**
 * @brief Return whether a directory contains a valid todo directory.
 *
 * @param path The directory to check.
 *
 * @return True if the given directory contains a local todo directory.
 */
bool contains_local_todo_dir(std::filesystem::path path);

/**
 * @brief Return the name used for the top level of local todo directories.
 *
 * @return A filesystem path with the name used for each local todo directory.
 */
std::filesystem::path get_local_todo_dir_name();

/**
 * @brief Get the directory containing all todo-related files.
 *
 * If global is set to false, then the function will search the current
 * directory, followed by each successive parent directory, until either a todo
 * directory is found or the home directory is reached.
 *
 * If no todo directory is found before or in the home directory, or global is
 * set to true, then this function will return a path to "<config_home>/todo"
 * where "<config_home>" is the value returned by util::xdg::config_home.
 *
 * @param global Whether to return the global or local todo directory.
 *
 * @return A filesystem path to the directory containing all todo files.
 */
std::filesystem::path get_todo_dir(bool global);

/**
 * @brief Get a list of todo directories from and above the current directory.
 *
 * The generated list will be include the current directory, if it contains a
 * todo directory, followed by each successive parent directory that contains a
 * todo directory, until the home directory is reached.
 *
 * If the function is run outside of the users' home directory, then the list
 * will continue traversing parents until the root directory is reached.
 *
 * The global todo directory will always be included in the list.
 *
 * @return A vector of filesystem paths to todo directories.
 */
std::vector<std::filesystem::path> get_local_todo_dir_hierarchy();

} // namespace file
} // namespace todo

#endif
