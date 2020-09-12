#ifndef TASK_URGENT_H
#define TASK_URGENT_H

#include "task/task.hpp"
#include "task/outstanding_abstract.hpp"

namespace task {

class Urgent : public OutstandingAbstract {

    public:
        Urgent();

    private:
        std::string format(const Task& task) override;
};

} // namespace task

#endif
