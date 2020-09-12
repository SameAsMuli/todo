#include "task/task.hpp"
#include "task/complete_abstract.hpp"

#ifndef TASK_REJECTED_H
#define TASK_REJECTED_H

namespace task {

class Rejected : public CompleteAbstract {

    public:
        Rejected();

    private:
        std::string format(const Task& task) override;
};

} // namespace task

#endif
