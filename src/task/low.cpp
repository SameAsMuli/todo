#include <sstream> // std::stringstream

#include "task/low.hpp"
#include "util/ansi.hpp"

namespace task {

Low::Low() : OutstandingAbstract('~') {}

std::string Low::format(const Task &task) {
    std::stringstream ss;

    ss << util::ansi::foreground_blue << task.getPrefix() << util::ansi::reset
       << " " << task.getDescription();

    return ss.str();
}

} // namespace task
