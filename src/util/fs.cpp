#include <cstdlib>  // std::getenv
#include <pwd.h>    // getpwuid
#include <string>   // std::string
#include <unistd.h> // getuid

#include "util/fs.hpp"

namespace util {
namespace fs {

std::filesystem::path HomeDir()
{
    std::string home = std::getenv("HOME");

    if (!home.empty()) {
        return std::filesystem::path{home};
    }

    struct passwd* pwd = getpwuid(getuid());

    if (pwd != nullptr) {
        return pwd->pw_dir;
    }

    // if we got here both getenv() and getpwuid() failed so let's just
    // return an empty Path to indicate failure
    return {};
}

} // namespace fs
} // namespace util
