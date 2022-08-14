#ifndef TASK_TASK_H
#define TASK_TASK_H

#include <iostream> // std::istream
#include <string>   // std::string

#include "task/type.hpp"
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
     * @brief Create a task with a given type and description.
     *
     * @param type The type of the task.
     * @param description The description for the task.
     */
    Task(Type type, std::string &description);

    /**
     * @brief Get the type for this task.
     *
     * @return The type of this task.
     */
    Type get_type() const { return m_type; }

    /**
     * @brief Get the description for this task.
     *
     * @return The description for this task.
     */
    std::string get_description() const { return m_description; }

    /**
     * @brief Return the time the task was added (as the current task type).
     *
     * The task may have previously existed as an outstanding task before then
     * being added as a completed task instead. In that situation this function
     * should return the time the task was added as complete, not when it was
     * first added as an outstanding task.
     *
     * @return A chrono time point indicating when the task was added.
     */
    std::chrono::system_clock::time_point get_time_added() const {
        return m_timeAdded;
    }

    /**
     * @brief Return the task's former type if it had one.
     *
     * A task may be added as one type and then re-added as another type. In
     * this case the previous task type's type is returned. If there is no
     * previous task type then ' ' is returned.
     *
     * @return The previous type or UNKNOWN_TYPE, if none exists.
     */
    Type get_previous_type() const { return m_previousType; }

    /**
     * @brief Return the time the task was added (as the previous task type).
     *
     * A task may be added as one type and then re-added as another type. In
     * this case the previous task's time added is returned. If there is no
     * previous time added then the start of system_clock is returned.
     *
     * @return A chrono time point for the addition of the previous type.
     */
    std::chrono::system_clock::time_point get_previous_time_added() const {
        return m_previousTimeAdded;
    }

    /**
     * @brief Set the type for this task.
     *
     * @param type The type to use.
     *
     * @{
     */
    void set_type(const Type &type) { m_type = type; }
    void set_type(const Type &&type) { m_type = type; }
    /** @} */

    /**
     * @brief Set the description for this task.
     *
     * @param description The description to use.
     *
     * @{
     */
    void set_description(const std::string &description);
    void set_description(const std::string &&description);
    /** @} */

    /**
     * @brief Set the time the task was added (as its current task type).
     *
     * @param timeAdded A chrono time point indicating when the task was added.
     *
     * @{
     */
    void
    set_time_added(const std::chrono::system_clock::time_point &timeAdded) {
        m_timeAdded = timeAdded;
    }
    void
    set_time_added(const std::chrono::system_clock::time_point &&timeAdded) {
        m_timeAdded = timeAdded;
    }
    /** @} */

    /**
     * @brief Set the former type for this task.
     *
     * @param previousType The previous type.
     */
    void set_previous_type(const Type &previousType) {
        m_previousType = previousType;
    }

    /**
     * @brief Set the time the task was added (as the previous task type).
     *
     * @param timeAdded A chrono time point for addition of the previous type.
     *
     * @{
     */
    void set_previous_time_added(
        const std::chrono::system_clock::time_point &timeAdded) {
        m_previousTimeAdded = timeAdded;
    }
    void set_previous_time_added(
        const std::chrono::system_clock::time_point &&timeAdded) {
        m_previousTimeAdded = timeAdded;
    }
    /** @} */

    /**
     * @brief Output a task to a given stream.
     *
     * Formats the task with colour.
     *
     * @param stream The stream to use.
     * @param task The task to use.
     *
     * @return The given stream.
     */
    friend std::ostream &operator<<(std::ostream &stream, const Task &task);

  private:
    Type m_type;

    std::string m_description;

    std::chrono::system_clock::time_point m_timeAdded;

    Type m_previousType;

    std::chrono::system_clock::time_point m_previousTimeAdded;
};

} // namespace task
} // namespace todo

#endif
