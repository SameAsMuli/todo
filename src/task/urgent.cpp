#include <sstream> // std::stringstream

#include "task/urgent.hpp"
#include "util/ansi.hpp"

namespace todo {
namespace task {

Urgent::Urgent() : OutstandingAbstract('#') {}

std::string Urgent::format(const Task &task) {
    std::stringstream ss;

    ss << util::ansi::foreground_red << util::ansi::bold << "! "
       << task.getDescription() << util::ansi::reset;

    return ss.str();
}

} // namespace task
} // namespace todo
