#ifndef TODO_FILES_H
#define TODO_FILES_H

#include <filesystem> // std::filesystem

namespace todo {
namespace files {

void initialise();

std::filesystem::path getOutstanding();

std::filesystem::path getComplete();

std::filesystem::path getTemp();

std::filesystem::path getTodoDir();

} // namespace files
} // namespace todo

#endif
