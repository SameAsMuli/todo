#include <filesystem> // std::filesystem
#include <vector>     // std::vector

#ifndef UTIL_XDG_H
#define UTIL_XDG_H

namespace util {
namespace xdg {

std::filesystem::path configHome();

std::filesystem::path dataHome();

std::vector<std::filesystem::path> configDirs();

std::vector<std::filesystem::path> dataDirs();

std::filesystem::path cacheHome();

std::filesystem::path runtimeDir();

} // namespace xdg
} // namespace util

#endif
