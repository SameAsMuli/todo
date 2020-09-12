#ifndef TASK_URGENT_H
#define TASK_URGENT_H

#include "task/outstanding_abstract.hpp"
#include "task/task.hpp"

namespace task {

class Urgent : public OutstandingAbstract {

  public:
    Urgent();

  private:
    std::string format(const Task &task) override;
};

} // namespace task

#endif
