#include <sstream> // std::stringstream

#include "task/urgent.hpp"
#include "util/ansi.hpp"

namespace task {

Urgent::Urgent() : OutstandingAbstract('!')
{ }

std::string Urgent::format(const Task& task)
{
    std::stringstream ss;

    ss << util::ansi::foreground_red << util::ansi::bold << task.getPrefix()
        << " " << task.getDescription() << util::ansi::reset ;

    return ss.str();
}

} // namespace task
