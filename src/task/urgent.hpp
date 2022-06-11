#ifndef TASK_URGENT_H
#define TASK_URGENT_H

#include "task/outstanding_abstract.hpp"
#include "task/task.hpp"

namespace todo {
namespace task {

/**
 * @brief Task type to govern an urgent task.
 *
 * This indicates an urgent priority task that needs completing as soon as
 * possible.
 */
class Urgent : public OutstandingAbstract {

  public:
    Urgent();
};

} // namespace task
} // namespace todo

#endif
