#include <sstream> // std::stringstream

#include "task/normal.hpp"
#include "util/ansi.hpp"

namespace task {

Normal::Normal() : OutstandingAbstract('-')
{ }

std::string Normal::format(const Task& task)
{
    std::stringstream ss;

    ss << util::ansi::foreground_red << task.getPrefix()
        << util::ansi::reset << " " << task.getDescription();

    return ss.str();
}

} // namespace task
