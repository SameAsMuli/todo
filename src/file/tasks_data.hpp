#ifndef FILE_TASKS_DATA_H
#define FILE_TASKS_DATA_H

#include <functional> // std::function

#include "file/data_abstract.hpp"
#include "task/task.hpp"

namespace todo {
namespace file {

/**
 * @brief Class representing the tasks data file.
 *
 * This class defines the object representation of the tasks data file, allowing
 * simple serialization/de-serialization between itself and the data file.
 */
class TasksData : public DataAbstract {

  public:
    /**
     * @brief Construct the class, referencing a specific tasks file.
     *
     * This function will read the file and populate this class with the
     * contents.
     *
     * @param fileType The type of tasks file to open.
     * @param global Whether to consider the global or local tasks file.
     */
    TasksData(File fileType, bool global = false);

    /**
     * @brief Add a task to the task list file.
     *
     * @param task The task to add to the file.
     */
    void addTask(const task::Task &task);

    /**
     * @brief Remove a task if it meets a certain criteria.
     *
     * @param matchFunc A callback describing the matching condition.
     *
     * @return The number of tasks that were removed.
     */
    unsigned int removeTasks(std::function<bool(const task::Task &)> matchFunc);

    /**
     * @brief Search all stored tasks and return any matches.
     *
     * @param searchFunc A callback describing the search criteria.
     *
     * @return A vector of matching tasks.
     */
    std::vector<task::Task>
    search(std::function<bool(const task::Task &)> searchFunc) const;

    /**
     * @brief Loop all stored tasks and perform an action on each one.
     *
     * @param function A callback describing the action to perform on each task.
     */
    void forEach(std::function<void(task::Task &)> function);

  private:
    std::vector<task::Task> m_tasks;

    /**
     * @brief Read the tasks data file into this class instance.
     */
    void read_derived() override;

    /**
     * @brief Write this class's data to the tasks data file.
     */
    void write_derived() const override;

    /**
     * @brief Put an empty array in the tasks file if it's currently empty.
     */
    void initialiseFile_derived() const override;
};

} // namespace file
} // namespace todo

#endif
