#ifndef ACTION_ADD_H
#define ACTION_ADD_H

#include <string> // std::string

#include "action/action_abstract.hpp"
#include "input/input.hpp"
#include "task/task_type_abstract.hpp"
#include "task/type.hpp"

namespace todo {
namespace action {

/**
 * @brief Action to add tasks of a given type.
 */
class Add : public ActionAbstract {

  public:
    /**
     * @brief Base constructor for an add action.
     *
     * @param taskType The type of task this class will add.
     */
    Add(const task::Type taskType);

    /**
     * @brief Get the type of task added by this action.
     *
     * @return The task type for this action.
     */
    task::Type getTaskType() const { return m_taskType; }

    /**
     * @brief Get the usage details of the add action.
     *
     * @return A string with the usage text of the add action.
     */
    std::string usage() const override;

    /**
     * @brief Get a detailed description of the add action.
     *
     * @return A string with the description of the add action.
     */
    std::string description() const override;

  private:
    const task::Type m_taskType;

    /**
     * @brief Add a todo task.
     */
    void run(const input::Input &input) override;
};

} // namespace action
} // namespace todo

#endif
