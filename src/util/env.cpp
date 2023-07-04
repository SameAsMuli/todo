#include <iostream> // std::cout
#include <stdlib.h> // std::getenv
#include <string>   // std::string

#include "util/env.hpp"
#include "util/fs.hpp"

namespace util {
namespace env {

bool command_exists(const std::string &command) {
    if (command.empty()) {
        return false;
    }

    /* If command is a path, check it directly */
    if (command.find('/') != std::string::npos) {
        return fs::is_executable(std::filesystem::path{command});
    }

    /* Otherwise, check if the command is in the PATH */
    auto var = std::getenv("PATH");
    if (var == NULL) {
        return false;
    }

    std::string path = std::string{var};
    size_t start_pos = 0, end_pos = 0;

    if (path.empty()) {
        return false;
    }

    while ((end_pos = path.find(':', start_pos)) != std::string::npos) {
        std::string current_path =
            path.substr(start_pos, end_pos - start_pos) + "/" + command;

        if (fs::is_executable(std::filesystem::path{current_path})) {
            return true;
        }

        start_pos = end_pos + 1;
    }

    return false;
}

} // namespace env
} // namespace util
