#include <sstream> // std::stringstream

#include "task/rejected.hpp"
#include "util/ansi.hpp"

namespace task {

Rejected::Rejected() : CompleteAbstract('/') {}

std::string Rejected::format(const Task &task) {
    std::stringstream ss;

    ss << util::ansi::foreground_red << task.getPrefix() << " "
       << task.getDescription() << util::ansi::reset;

    return ss.str();
}

} // namespace task
