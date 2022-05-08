#ifndef TASK_TASK_H
#define TASK_TASK_H

#include <iostream> // std::istream

#include "task/metadata.hpp"
#include "task/prefix.hpp"
#include "util/string.hpp"

namespace todo {
namespace task {

/**
 * @brief Class to hold information about a specific task.
 */
class Task {

  public:
    Task();

    /**
     * @brief Create a task with a given prefix and description.
     *
     * @param prefix The prefix for the task.
     * @param description The description for the task.
     */
    Task(Prefix prefix, std::string &description);

    /**
     * @brief Get the metadata for this task.
     *
     * @return The metadata object associated with this task.
     */
    Metadata getMetadata() const { return m_metadata; }

    /**
     * @brief Get the prefix for this task.
     *
     * @return The character that prefixes this task.
     */
    Prefix getPrefix() const { return m_prefix; }

    /**
     * @brief Get the description for this task.
     *
     * @return The description for this task.
     */
    std::string getDescription() const { return m_description; }

    /**
     * @brief Set the prefix for this task.
     *
     * @param prefix The prefix to use.
     */
    void setPrefix(Prefix prefix) { m_prefix = prefix; }

    /**
     * @brief Set the description for this task.
     *
     * @param description The description to use.
     */
    void setDescription(std::string &description);

    /**
     * @brief Set the metadata for the task.
     *
     * @param metadata The metadata object to add to the task.
     */
    void setMetadata(Metadata metadata) { m_metadata = metadata; }

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
    friend std::ostream &operator<<(std::ostream &stream, const Task &task);

  private:
    Metadata m_metadata;

    Prefix m_prefix;

    std::string m_description;
};

} // namespace task
} // namespace todo

#endif
