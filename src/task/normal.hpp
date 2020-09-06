#include "task/task.hpp"
#include "task/outstanding_abstract.hpp"

#ifndef TASK_NORMAL_H
#define TASK_NORMAL_H

namespace task {

class Normal : public OutstandingAbstract {

    public:
        Normal();

    private:
        std::string format(const Task& task) override;
};

} // namespace task

#endif
