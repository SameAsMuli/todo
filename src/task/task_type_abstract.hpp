#ifndef TASK_TASK_TYPE_ABSTRACT_H
#define TASK_TASK_TYPE_ABSTRACT_H

#include <filesystem> // std::filesystem
#include <functional> // std::function
#include <string>     // std::string

#include "input/input.hpp"
#include "task/task.hpp"

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
     * @param f_file Function to return the file used to store the task type.
     * @param name The name of the task type.
     * @param prefix The prefix for the task type.
     */
    TaskTypeAbstract(const std::function<std::filesystem::path(bool)> &f_file,
                     const std::string &name, const Prefix &prefix);

    /**
     * @brief Get the data file into which this task type is written.
     *
     * @param global Whether to consider local or global only tasks.
     *
     * @return A filesystem path to the data file.
     */
    std::filesystem::path getFile(bool global = false) const;

    /**
     * @brief Get the name of the task type.
     *
     * @return A string containing the name of this task type.
     */
    std::string getName() const { return m_name; }

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
    virtual void add(const input::Input &input) = 0;

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
    const std::function<std::filesystem::path(bool)> m_f_file;

    const std::string m_name;

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
