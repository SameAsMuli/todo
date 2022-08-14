#include <stdexcept> // std::runtime_error
#include <string>    // std::string

#include "util/fs.hpp"
#include "util/xdg.hpp"

namespace {

/**
 * @brief Split a string into a vector of filesystem paths.
 *
 * @param str The string to split.
 * @param delim The delimiting character to split on.
 *
 * @return A vector of filesystem paths.
 */
std::vector<std::filesystem::path> split(const std::string &str, char delim) {
    static std::vector<std::filesystem::path> strings;
    size_t start;
    size_t end = 0;
    while ((start = str.find_first_not_of(delim, end)) != std::string::npos) {
        end = str.find(delim, start);
        strings.push_back(
            std::filesystem::path{str.substr(start, end - start)});
    }
    return strings;
}

/**
 * @brief Get a filesystem path from an environment variable.
 *
 * @param varName The environment variable name to check.
 * @param defaultValue A default path to use if varName is empty.
 *
 * @return A filesystem path from varName or defaultValue.
 */
std::filesystem::path get_env_dir(const char *varName,
                                  std::string defaultValue) {
    auto value = std::getenv(varName);
    static std::filesystem::path path;

    if (value != NULL) {
        path = std::filesystem::path{value};
    } else {
        path = defaultValue;
    }

    return path;
}

/**
 * @brief Get a vector of filesystem paths from an environment variable.
 *
 * @param varName The environment variable to check.
 * @param defaultValue A default collection of paths to use if varName is empty.
 *
 * @return A vector of filesystem paths from varName or defaultValue.
 */
std::vector<std::filesystem::path> get_env_dirs(const char *varName,
                                                std::string defaultValue) {
    auto value = std::getenv(varName);
    std::string listString;

    if (value != NULL) {
        listString = std::string{value};
    } else {
        listString = std::string{defaultValue};
    }

    return split(listString, ':');
}

} // namespace

namespace util {
namespace xdg {

std::filesystem::path config_home() {
    return get_env_dir("XDG_CONFIG_HOME", util::fs::home_dir() / ".config");
}

std::filesystem::path data_home() {
    return get_env_dir("XDG_DATA_HOME", util::fs::home_dir() / ".local/share");
}

std::vector<std::filesystem::path> config_dirs() {
    return get_env_dirs("XDG_CONFIG_DIRS", "/etc/xdg");
}

std::vector<std::filesystem::path> data_dirs() {
    return get_env_dirs("XDG_DATA_DIRS", "/usr/local/share/:/usr/share/");
}

std::filesystem::path cache_home() {
    return get_env_dir("XDG_CACHE_HOME", util::fs::home_dir() / ".cache");
}

std::filesystem::path runtime_dir() {
    auto value = std::getenv("XDG_RUNTIME_DIR");

    if (value == NULL) {
        throw std::runtime_error("XDG_RUNTIME_DIR not set in the environment.");
    }

    return std::filesystem::path{value};
}

} // namespace xdg
} // namespace util
