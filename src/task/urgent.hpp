#ifndef TASK_URGENT_H
#define TASK_URGENT_H

#include "task/outstanding_abstract.hpp"
#include "task/task.hpp"

namespace task {

/**
 * @brief Task type to govern an urgent task.
 *
 * This indicates a high priority task that needs completing urgently.
 */
class Urgent : public OutstandingAbstract {

  public:
    Urgent();

  private:
    std::string format(const Task &task) override;
};

} // namespace task

#endif
