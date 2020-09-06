#include "task/done.hpp"

namespace task {

Done::Done() : CompleteAbstract('+')
{ }

std::string Done::format(const Task& task)
{
    /* TODO-SAM Add colour to done tasks */
    return task.getPrefix() + std::string{" "} + task.getDescription();
}

} // namespace task
