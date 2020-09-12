#ifndef TASK_OUTSTANDING_ABSTRACT_H
#define TASK_OUTSTANDING_ABSTRACT_H

#include "task/task.hpp"
#include "task/task_type_abstract.hpp"

namespace task {

class OutstandingAbstract : public TaskTypeAbstract {

    public:
        OutstandingAbstract(char prefix);

        void add(const util::Input& input) override;
};

} // namespace task

#endif
