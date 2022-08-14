#include <cstdlib>    // std::getenv
#include <cstring>    // std::strlen
#include <fstream>    // std::ofstream
#include <pwd.h>      // getpwuid
#include <string>     // std::string
#include <sys/stat.h> // struct stat
#include <unistd.h>   // getcwd, getuid, PATH_MAX

#include "util/fs.hpp"

namespace util {
namespace fs {

std::filesystem::path current_dir() {
    try {
        return std::filesystem::current_path();
    } catch (const std::exception &e) {
        /* If we got here, getcwd() has failed so let's just return an empty
         * Path to indicate failure.
         */
        return {};
    }
}

std::filesystem::path home_dir() {
    /* Use user's $HOME if running as a snap */
    auto home = std::getenv("SNAP_REAL_HOME");
    if (home != NULL && std::strlen(home) > 0) {
        return std::filesystem::path{home};
    }

    home = std::getenv("HOME");
    if (home != NULL && std::strlen(home) > 0) {
        return std::filesystem::path{home};
    }

    struct passwd *pwd = getpwuid(getuid());
    if (pwd != nullptr) {
        return pwd->pw_dir;
    }

    /* If we got here, both getenv() and getpwuid() have failed so let's just
     * return an empty Path to indicate failure.
     */
    return {};
}

std::filesystem::path root_dir() {
    try {
        return current_dir().root_path();
    } catch (const std::exception &e) {
        /* If we got here, getcwd() has failed so let's just return an empty
         * Path to indicate failure.
         */
        return {};
    }
}

void init_dir(const std::filesystem::path dir) {
    std::filesystem::create_directories(dir);
}

void init_file(const std::filesystem::path &file) {
    /* Create parent directory if it doesn't already exist */
    std::filesystem::create_directories(file.parent_path());

    /* Create file if it doesn't already exist */
    if (!std::filesystem::exists(file)) {
        std::ofstream(file.string());
    }
}

bool is_executable(const std::string &path) {
    struct stat sb;
    if ((stat(path.c_str(), &sb) == 0) && (sb.st_mode & S_IXOTH)) {
        return (sb.st_mode & S_IXUSR) != 0;
    }
    return false;
}

} // namespace fs
} // namespace util
