#ifndef TASK_NORMAL_H
#define TASK_NORMAL_H

#include "task/outstanding_abstract.hpp"
#include "task/task.hpp"

namespace task {

class Normal : public OutstandingAbstract {

  public:
    Normal();

  private:
    std::string format(const Task &task) override;
};

} // namespace task

#endif
