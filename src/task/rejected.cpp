#include <sstream> // std::stringstream

#include "task/rejected.hpp"
#include "util/ansi.hpp"

namespace todo {
namespace task {

Rejected::Rejected() : CompleteAbstract("rejected", '/') {}

std::string Rejected::format(const Task &task) {
    std::stringstream ss;

    ss << util::ansi::foreground_red << task.getType() << " "
       << task.getDescription() << util::ansi::reset;

    return ss.str();
}

} // namespace task
} // namespace todo
