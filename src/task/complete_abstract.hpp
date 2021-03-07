#ifndef TASK_COMPLETE_ABSTRACT_H
#define TASK_COMPLETE_ABSTRACT_H

#include "task/task.hpp"
#include "task/task_type_abstract.hpp"

namespace todo {
namespace task {

/**
 * @brief Abstract class to govern completed task types.
 */
class CompleteAbstract : public TaskTypeAbstract {

  public:
    /**
     * @brief Base constructor for completed task types.
     *
     * @param name The name of the task type.
     * @param prefix The prefix for the task type.
     */
    CompleteAbstract(const std::string &name, const Prefix &prefix);

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
    void add(const input::Input &input) override;

    /**
     * @brief Find a task in complete_tasks and move it to outstanding_tasks.
     *
     * Look for a task in the complete_tasks data file that matches a given
     * substring. Once found, remove the task and add it to the
     * outstanding_tasks data file.
     *
     * An exception is thrown if no task is matched or more than one task is
     * matched. Any file access problems will also throw an error.
     *
     * @param input The substring to search for.
     */
    static void undo(const input::Input &input);
};

} // namespace task
} // namespace todo

#endif
