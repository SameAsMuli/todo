#ifndef TASK_DONE_H
#define TASK_DONE_H

#include "task/complete_abstract.hpp"
#include "task/task.hpp"

namespace todo {
namespace task {

/**
 * @brief Task type to govern a done task.
 *
 * Done tasks are ones that have been actively fulfilled and so should be
 * removed from the outstanding tasks.
 */
class Done : public CompleteAbstract {

  public:
    Done();
};

} // namespace task
} // namespace todo

#endif
