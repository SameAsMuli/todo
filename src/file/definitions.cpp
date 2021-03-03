#include "file/definitions.hpp"
#include "util/fs.hpp"
#include "util/xdg.hpp"

namespace {

/**
 * @brief Return the name used for local todo directories.
 *
 * @return A filesystem path with the name used for local todo directories.
 */
std::filesystem::path localTodoDirName() {
    return std::filesystem::path{".todo"};
}

/**
 * @brief Return whether a directory conatins a valid todo directory.
 *
 * @param path The directory to check.
 *
 * @return True if the given directory contains a local todo directory.
 */
bool containsLocalTodoDir(std::filesystem::path path) {
    return std::filesystem::is_directory(path / localTodoDirName());
}

/**
 * @brief Return the global todo directory.
 *
 * @return A filesystem path to the global todo directory.
 */
std::filesystem::path globalTodoDir() {
    return util::xdg::configHome() / "todo";
}

} // namespace

namespace todo {
namespace file {

std::filesystem::path getOutstanding(bool global) {
    return getTodoDir(global) / "outstanding_tasks";
}

std::filesystem::path getComplete(bool global) {
    return getTodoDir(global) / "complete_tasks";
}

std::filesystem::path getArchive(bool global) {
    return getTodoDir(global) / "archive";
}

std::filesystem::path getTemp() { return getTodoDir(true) / "temp"; }

std::filesystem::path getTodoDir(bool global) {
    if (!global) {
        auto dir = util::fs::CurrentDir();
        if (dir.empty()) {
            return globalTodoDir();
        }

        /* Check now in case we're currently in the home directory */
        if (containsLocalTodoDir(dir)) {
            return dir;
        }

        while (dir != util::fs::HomeDir() && dir != dir.parent_path()) {
            dir = dir.parent_path();
            if (containsLocalTodoDir(dir)) {
                return dir;
            }
        }
    }

    return globalTodoDir();
}

} // namespace file
} // namespace todo
