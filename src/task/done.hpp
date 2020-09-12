#ifndef TASK_DONE_H
#define TASK_DONE_H

#include "task/task.hpp"
#include "task/complete_abstract.hpp"

namespace task {

class Done : public CompleteAbstract {

    public:
        Done();

    private:
        std::string format(const Task& task) override;
};

} // namespace task

#endif
