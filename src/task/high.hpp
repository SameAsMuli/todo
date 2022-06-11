#ifndef TASK_HIGH_H
#define TASK_HIGH_H

#include "task/outstanding_abstract.hpp"
#include "task/task.hpp"

namespace todo {
namespace task {

/**
 * @brief Task type to govern a high priority task.
 *
 * This indicates a high priority task that needs completing soon.
 */
class High : public OutstandingAbstract {

  public:
    High();
};

} // namespace task
} // namespace todo

#endif
