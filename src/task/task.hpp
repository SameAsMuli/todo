#ifndef TASK_TASK_H
#define TASK_TASK_H

#include <iostream> // std::istream

namespace task {

/**
 * @brief Class to hold information about a specific task.
 */
class Task {

  public:
    Task();

    /**
     * @brief Get the prefix for this task.
     *
     * @return The character that prefixes this task.
     */
    char getPrefix() const { return m_prefix; }

    /**
     * @brief Get the description for this task.
     *
     * @return The description for this task.
     */
    std::string getDescription() const { return m_description; }

    /**
     * @brief Populate a task from a stream.
     *
     * If the stream cannot be fully converted to a task then it has the failbit
     * set against it.
     *
     * @param stream The stream to use.
     * @param task The task to populate.
     *
     * @return The given stream.
     */
    friend std::istream &operator>>(std::istream &stream, Task &task);

    /**
     * @brief Output a task to a given stream.
     *
     * Sends the prefix and description to the stream, separated by a space.
     *
     * @param stream The stream to use.
     * @param task The task to use.
     *
     * @return The given stream.
     */
    friend std::ostream &operator<<(std::ostream &stream, Task &task);

  private:
    char m_prefix;

    std::string m_description;
};

} // namespace task

#endif
