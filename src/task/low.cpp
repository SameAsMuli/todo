#include <sstream> // std::stringstream

#include "task/low.hpp"
#include "util/ansi.hpp"

namespace todo {
namespace task {

Low::Low() : OutstandingAbstract("low", '~') {}

std::string Low::format(const Task &task) {
    std::stringstream ss;

    ss << util::ansi::foreground_blue << task.getType() << util::ansi::reset
       << " " << task.getDescription();

    return ss.str();
}

} // namespace task
} // namespace todo
