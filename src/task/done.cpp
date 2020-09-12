#include <sstream> // std::stringstream

#include "task/done.hpp"
#include "util/ansi.hpp"

namespace task {

Done::Done() : CompleteAbstract('+')
{ }

std::string Done::format(const Task& task)
{
    std::stringstream ss;

    ss << util::ansi::foreground_green << task.getPrefix()
        << util::ansi::reset << " " << task.getDescription();

    return ss.str();
}

} // namespace task
