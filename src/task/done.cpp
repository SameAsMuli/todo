#include <sstream> // std::stringstream

#include "task/done.hpp"
#include "util/ansi.hpp"

namespace todo {
namespace task {

Done::Done() : CompleteAbstract("done", '+') {}

std::string Done::format(const Task &task) {
    std::stringstream ss;

    ss << util::ansi::foreground_green << task.getPrefix() << util::ansi::reset
       << " " << task.getDescription();

    return ss.str();
}

} // namespace task
} // namespace todo
