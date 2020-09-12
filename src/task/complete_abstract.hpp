#ifndef TASK_COMPLETE_ABSTRACT_H
#define TASK_COMPLETE_ABSTRACT_H

#include "task/task.hpp"
#include "task/task_type_abstract.hpp"

namespace task {

class CompleteAbstract : public TaskTypeAbstract {

  public:
    CompleteAbstract(char prefix);

    void add(const util::Input &input) override;
};

} // namespace task

#endif
