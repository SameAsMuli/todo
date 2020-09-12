#include "task/task.hpp"
#include "task/outstanding_abstract.hpp"

#ifndef TASK_LOW_H
#define TASK_LOW_H

namespace task {

class Low : public OutstandingAbstract {

    public:
        Low();

    private:
        std::string format(const Task& task) override;
};

} // namespace task

#endif
