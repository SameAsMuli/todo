#ifndef TASK_LOW_H
#define TASK_LOW_H

#include "task/task.hpp"
#include "task/outstanding_abstract.hpp"

namespace task {

class Low : public OutstandingAbstract {

    public:
        Low();

    private:
        std::string format(const Task& task) override;
};

} // namespace task

#endif
