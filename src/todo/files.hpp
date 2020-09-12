#include <filesystem> // std::filesystem

namespace fs = std::filesystem;

#ifndef TODO_FILES_H
#define TODO_FILES_H

namespace todo {
namespace files {

void initialise();

fs::path getOutstanding();

fs::path getComplete();

fs::path getTemp();

fs::path getTodoDir();

} // namespace files
} // namespace todo

#endif
