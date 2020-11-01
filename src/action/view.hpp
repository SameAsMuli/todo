#ifndef ACTION_VIEW_H
#define ACTION_VIEW_H

#include <filesystem> //std::filesystem

#include "action/action_abstract.hpp"
#include "task/task_type_abstract.hpp"

namespace todo {
namespace action {

/**
 * @brief Action to view different task types.
 */
class View : public ActionAbstract {

  public:
    /**
     * @brief Initialise the view action.
     *
     * @param input The user's input.
     */
    View(const util::Input &input);

    /**
     * @brief Print all todo tasks.
     *
     * If the action has an empty input, all task types are printed. If the
     * input is non-empty, the input will be matched against a task type and
     * that type will be printed. If the input cannot be matched to a task type
     * then an exception will be thrown.
     */
    void run() override;

    /**
     * @brief Print all complete tasks.
     */
    void completeTodos() const;

    /**
     * @brief Print all outstanding tasks.
     */
    void outstandingTodos() const;

    /**
     * @brief Print all done tasks.
     */
    void doneTodos() const;

    /**
     * @brief Print all high tasks.
     */
    void highTodos() const;

    /**
     * @brief Print all low priority tasks.
     */
    void lowTodos() const;

    /**
     * @brief Print all normal priority tasks.
     */
    void normalTodos() const;

    /**
     * @brief Print all rejected tasks.
     */
    void rejectTodos() const;

    /**
     * @brief Print all urgent tasks.
     */
    void urgentTodos() const;

  private:
    /**
     * @brief Print all tasks of a given task type.
     *
     * @param taskType The task type to print.
     */
    void viewTodos(task::TaskTypeAbstract *const taskType) const;
};

#endif

} // namespace action
} // namespace todo
