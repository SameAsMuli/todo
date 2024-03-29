#ifndef TASK_METADATA_H
#define TASK_METADATA_H

#include <chrono>   // std::chrono
#include <iostream> // std::istream, std::ostream

#include "task/prefix.hpp"

namespace todo {
namespace task {

/**
 * @brief Class to hold meta-data about a specific task.
 */
class Metadata {

  public:
    Metadata();

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
    std::chrono::system_clock::time_point getTimeAdded() const {
        return m_timeAdded;
    }

    /**
     * @brief Return the task's former prefix if it had one.
     *
     * A task may be added as one type and then re-added as another type. In
     * this case the previous task type's prefix is returned. If there is no
     * previous task type then ' ' is returned.
     *
     * @return The previous prefix or ' ', if none exists.
     */
    Prefix getPreviousPrefix() const { return m_previousPrefix; }

    /**
     * @brief Return the time the task was added (as the previous task type).
     *
     * A task may be added as one type and then re-added as another type. In
     * this case the previous task's time added is returned. If there is no
     * previous time added then the start of system_clock is returned.
     *
     * @return A chrono time point for the addition of the previous prefix.
     */
    std::chrono::system_clock::time_point getPreviousTimeAdded() const {
        return m_previousTimeAdded;
    }

    /**
     * @brief Set the time the task was added (as its current task type).
     *
     * @param timeAdded A chrono time point indicating when the task was added.
     */
    void setTimeAdded(std::chrono::system_clock::time_point timeAdded) {
        m_timeAdded = timeAdded;
    }

    /**
     * @brief Set the former prefix for this task.
     *
     * @param previousPrefix The previous prefix.
     */
    void setPreviousPrefix(Prefix previousPrefix) {
        m_previousPrefix = previousPrefix;
    }

    /**
     * @brief Set the time the task was added (as the previous task type).
     *
     * @param timeAdded A chrono time point for addtion of the previous prefix.
     */
    void setPreviousTimeAdded(std::chrono::system_clock::time_point timeAdded) {
        m_previousTimeAdded = timeAdded;
    }

    /**
     * @brief Populate a task's metadata from a stream.
     *
     * If the stream has any unrecognised elements that cannot be stored within
     * the metadata class then it has the failbit set against it.
     *
     * @param stream The stream to use.
     * @param metadata The metadata object to populate.
     *
     * @return The given stream.
     */
    friend std::istream &operator>>(std::istream &stream, Metadata &metadata);

    /**
     * @brief Output a task's metadata to a given stream.
     *
     * Sends the timestamp added and previous prefix (if available) to the
     * stream.
     *
     * @param stream The stream to use.
     * @param metadata The metadata to use.
     *
     * @return The given stream.
     */
    friend std::ostream &operator<<(std::ostream &stream,
                                    const Metadata &metadata);

  private:
    std::chrono::system_clock::time_point m_timeAdded;

    Prefix m_previousPrefix;

    std::chrono::system_clock::time_point m_previousTimeAdded;
};

} // namespace task
} // namespace todo

#endif
