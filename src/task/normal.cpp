#include "task/normal.hpp"

namespace task {

Normal::Normal() : OutstandingAbstract('-')
{ }

std::string Normal::format(const Task& task)
{
    /* TODO-SAM Add colour to normal tasks */
    return task.getPrefix() + std::string{" "} + task.getDescription();
}

} // namespace task
