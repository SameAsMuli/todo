#include "file/definitions.hpp"
#include "util/xdg.hpp"

namespace todo {
namespace file {

std::filesystem::path getOutstanding() {
    return getTodoDir() / "outstanding_tasks";
}

std::filesystem::path getComplete() { return getTodoDir() / "complete_tasks"; }

std::filesystem::path getArchive() { return getTodoDir() / "archive"; }

std::filesystem::path getTemp() { return getTodoDir() / "temp"; }

std::filesystem::path getTodoDir() { return util::xdg::configHome() / "todo"; }

} // namespace file
} // namespace todo
