#include <sstream> // std::stringstream

#include "task/high.hpp"
#include "util/ansi.hpp"

namespace todo {
namespace task {

High::High() : OutstandingAbstract("high", '!') {}

std::string High::format(const Task &task) {
    std::stringstream ss;

    ss << util::ansi::foreground_red << task.getPrefix() << util::ansi::reset
       << " " << task.getDescription();

    return ss.str();
}

} // namespace task
} // namespace todo
