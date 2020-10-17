#ifndef TASK_TASK_TYPE_ABSTRACT_H
#define TASK_TASK_TYPE_ABSTRACT_H

#include <filesystem> // std::filesystem

#include "task/task.hpp"
#include "util/input.hpp"

namespace todo {
namespace task {

/**
 * @brief Defines how specific task types are viewed and added.
 */
class TaskTypeAbstract {

  public:
    /**
     * @brief Base constructor for a task type.
     *
     * @param file The file used to store the task type.
     * @param prefix The prefix for the task type.
     */
    TaskTypeAbstract(const std::filesystem::path &file, Prefix prefix);

    /**
     * @brief Get the data file into which this task type is written.
     *
     * @return A filesystem path to the data file.
     */
    std::filesystem::path getFile() const { return m_file; }

    /**
     * @brief Get the prefix for this task type.
     *
     * @return The character prefix for this task type.
     */
    Prefix getPrefix() const { return m_prefix; }

    /**
     * @brief Print all tasks of this task type.
     */
    void view();

    /**
     * @brief Add a task of this task type to the data file.
     *
     * @param input The input containing the description of the task.
     */
    virtual void add(const util::Input &input) = 0;

    /**
     * @brief Output a task type to a given stream.
     *
     * Sends the task type's prefix to the stream.
     *
     * @param stream The stream to use.
     * @param taskType The task type to use.
     *
     * @return The given stream.
     */
    friend std::ostream &operator<<(std::ostream &stream,
                                    const TaskTypeAbstract *taskType);

  private:
    const std::filesystem::path m_file;

    const Prefix m_prefix;

    /**
     * @brief Print a single task.
     *
     * Allows derived task types to define how they format their tasks.
     *
     * @param task The task to print.
     *
     * @return The formatted string representation of the given task.
     */
    virtual std::string format(const Task &task) = 0;
};

} // namespace task
} // namespace todo

#endif
