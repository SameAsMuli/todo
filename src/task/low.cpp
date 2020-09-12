#include "task/low.hpp"

namespace task {

Low::Low() : OutstandingAbstract('~')
{ }

std::string Low::format(const Task& task)
{
    /* TODO-SAM Add colour to low tasks */
    return task.getPrefix() + std::string{" "} + task.getDescription();
}

} // namespace task
