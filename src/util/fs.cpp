#include <cstdlib>  // std::getenv
#include <pwd.h>    // getpwuid
#include <string>   // std::string
#include <unistd.h> // getcwd, getuid, PATH_MAX

#include "util/fs.hpp"

namespace util {
namespace fs {

std::filesystem::path CurrentDir() {
    try {
        return std::filesystem::current_path();
    } catch (const std::exception &e) {
        /* If we got here, getcwd() has failed so let's just return an empty
         * Path to indicate failure.
         */
        return {};
    }
}

std::filesystem::path HomeDir() {
    std::string home = std::getenv("HOME");
    if (!home.empty()) {
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

std::filesystem::path RootDir() {
    try {
        return CurrentDir().root_path();
    } catch (const std::exception &e) {
        /* If we got here, getcwd() has failed so let's just return an empty
         * Path to indicate failure.
         */
        return {};
    }
}

} // namespace fs
} // namespace util
