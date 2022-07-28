#include "file/definitions.hpp"
#include "util/fs.hpp"
#include "util/xdg.hpp"

namespace {

/**
 * @brief Return whether a directory conatins a valid todo directory.
 *
 * @param path The directory to check.
 *
 * @return True if the given directory contains a local todo directory.
 */
bool containsLocalTodoDir(std::filesystem::path path) {
    return std::filesystem::is_directory(path /
                                         todo::file::getLocalTodoDirName());
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

std::filesystem::path getLocalTodoDirName() {
    return std::filesystem::path{".todo"};
}

std::filesystem::path getTodoDir(bool global) {
    if (!global) {
        auto dir = util::fs::CurrentDir();
        if (dir.empty()) {
            return globalTodoDir();
        }

        do {
            if (containsLocalTodoDir(dir)) {
                return dir / getLocalTodoDirName();
            }

            if (dir == util::fs::HomeDir()) {
                break;
            }

            dir = dir.parent_path();
        } while (dir != dir.parent_path());
    }

    return globalTodoDir();
}

} // namespace file
} // namespace todo
