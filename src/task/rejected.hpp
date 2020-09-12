#ifndef TASK_REJECTED_H
#define TASK_REJECTED_H

#include "task/complete_abstract.hpp"
#include "task/task.hpp"

namespace task {

class Rejected : public CompleteAbstract {

  public:
    Rejected();

  private:
    std::string format(const Task &task) override;
};

} // namespace task

#endif
