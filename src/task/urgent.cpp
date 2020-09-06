#include "task/urgent.hpp"

namespace task {

Urgent::Urgent() : OutstandingAbstract('!')
{ }

std::string Urgent::format(const Task& task)
{
    /* TODO-SAM Add colour to urgent tasks */
    return task.getPrefix() + std::string{" "} + task.getDescription();
}

} // namespace task
