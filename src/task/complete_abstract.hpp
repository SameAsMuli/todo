#ifndef TASK_COMPLETE_ABSTRACT_H
#define TASK_COMPLETE_ABSTRACT_H

#include "task/task.hpp"
#include "task/task_type_abstract.hpp"

namespace task {

/**
 * @brief Abstract class to govern completed task types.
 */
class CompleteAbstract : public TaskTypeAbstract {

  public:
    /**
     * @brief Base constructor for completed task types.
     *
     * @param prefix The prefix for the task type.
     */
    CompleteAbstract(Prefix prefix);

    /**
     * @brief Find a task in outstanding_tasks and move it to complete_tasks.
     *
     * Look for a task in the outstanding_tasks data file that matches a given
     * substring. Once found, remove the task and add it to the complete_tasks
     * data file.
     *
     * An exception is thrown if no task is matched or more than one task is
     * matched. Any file access problems will also throw an error.
     *
     * @param input The substring to search for.
     */
    void add(const util::Input &input) override;
};

} // namespace task

#endif
