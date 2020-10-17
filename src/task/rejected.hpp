#ifndef TASK_REJECTED_H
#define TASK_REJECTED_H

#include "task/complete_abstract.hpp"
#include "task/task.hpp"

namespace todo {
namespace task {

/**
 * @brief Task type to govern a rejected task.
 *
 * Rejected tasks are ones that haven't been actively fulfilled but that should
 * be removed from the outstanding tasks as they are no long necessary.
 */
class Rejected : public CompleteAbstract {

  public:
    Rejected();

  private:
    std::string format(const Task &task) override;
};

} // namespace task
} // namespace todo

#endif
