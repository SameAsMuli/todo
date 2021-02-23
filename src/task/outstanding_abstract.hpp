#ifndef TASK_OUTSTANDING_ABSTRACT_H
#define TASK_OUTSTANDING_ABSTRACT_H

#include <string> // std::string

#include "task/task.hpp"
#include "task/task_type_abstract.hpp"

namespace todo {
namespace task {

/**
 * @brief Abstract class to govern outstanding task types.
 */
class OutstandingAbstract : public TaskTypeAbstract {

  public:
    /**
     * @brief Base constructor for outstanding task types.
     *
     * @param name The name of the task type.
     * @param prefix The prefix for the task type.
     */
    OutstandingAbstract(const std::string &name, const Prefix &prefix);

    /**
     * @brief Add a task description to the outstanding_tasks data file.
     *
     * @param input The input containing the description.
     */
    void add(const util::Input &input) override;
};

} // namespace task
} // namespace todo

#endif
