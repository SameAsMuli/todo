#include "task/task.hpp"
#include "task/task_type_abstract.hpp"

#ifndef TASK_COMPLETE_ABSTRACT_H
#define TASK_COMPLETE_ABSTRACT_H

namespace task {

class CompleteAbstract : public TaskTypeAbstract {

    public:
        CompleteAbstract(char prefix);

        void add(const util::Input& input) override;
};

} // namespace task

#endif
