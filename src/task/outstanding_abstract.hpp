#include "task/task.hpp"
#include "task/task_type_abstract.hpp"

#ifndef TASK_OUTSTANDING_ABSTRACT_H
#define TASK_OUTSTANDING_ABSTRACT_H

namespace task {

class OutstandingAbstract : public TaskTypeAbstract {

    public:
        OutstandingAbstract(char prefix);

        void add(const util::Input& input) override;
};

} // namespace task

#endif
