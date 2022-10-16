#include "file/definitions.hpp"
#include "util/fs.hpp"
#include "util/xdg.hpp"

namespace {

/**
 * @brief Return the global todo directory.
 *
 * @return A filesystem path to the global todo directory.
 */
std::filesystem::path global_todo_dir() {
    return util::xdg::config_home() / "todo";
}

} // namespace

namespace todo {
namespace file {

bool contains_local_todo_dir(std::filesystem::path path) {
    return std::filesystem::is_directory(path / get_local_todo_dir_name());
}

std::filesystem::path get_local_todo_dir_name() {
    return std::filesystem::path{".todo"};
}

std::filesystem::path get_todo_dir(bool global) {
    if (!global) {
        auto dir = util::fs::current_dir();
        if (dir.empty()) {
            return global_todo_dir();
        }

        do {
            if (contains_local_todo_dir(dir)) {
                return dir / get_local_todo_dir_name();
            }

            if (dir == util::fs::home_dir()) {
                break;
            }

            dir = dir.parent_path();
        } while (dir != dir.parent_path());
    }

    return global_todo_dir();
}

std::vector<std::filesystem::path> get_local_todo_dir_hierarchy() {
    std::vector<std::filesystem::path> dirs;

    auto dir = util::fs::current_dir();
    if (!dir.empty()) {
        auto home_dir = util::fs::home_dir();
        do {
            if (contains_local_todo_dir(dir)) {
                dirs.push_back(dir / get_local_todo_dir_name());
            }

            if (dir == home_dir) {
                break;
            }

            dir = dir.parent_path();
        } while (dir != dir.parent_path());
    }

    dirs.push_back(global_todo_dir());
    return dirs;
}

} // namespace file
} // namespace todo
