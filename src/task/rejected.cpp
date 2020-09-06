#include "task/rejected.hpp"

namespace task {

Rejected::Rejected() : CompleteAbstract('/')
{ }

std::string Rejected::format(const Task& task)
{
    /* TODO-SAM Add colour to rejected tasks */
    return task.getPrefix() + std::string{" "} + task.getDescription();
}

} // namespace task
