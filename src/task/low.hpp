#ifndef TASK_LOW_H
#define TASK_LOW_H

#include "task/outstanding_abstract.hpp"
#include "task/task.hpp"

namespace task {

/**
 * @brief Task type to govern a low priority task.
 *
 * This indicates a minimal priority task that can be left for some time.
 */
class Low : public OutstandingAbstract {

  public:
    Low();

  private:
    std::string format(const Task &task) override;
};

} // namespace task

#endif
