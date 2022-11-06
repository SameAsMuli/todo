#ifndef ACTION_COMPLETE_H
#define ACTION_COMPLETE_H

#include <string> // std::string

#include "action/action_abstract.hpp"
#include "input/input.hpp"
#include "task/type.hpp"

namespace todo {
namespace action {

/**
 * @brief Action to make an outstanding task as complete.
 */
class Complete : public ActionAbstract {

  public:
    /**
     * @brief Base constructor for a completion action.
     *
     * @param taskType The new type this class will give to completed tasks.
     */
    explicit Complete(const task::Type taskType);

    /**
     * @brief Get the completion type used by this action.
     *
     * @return The task type for this action.
     */
    task::Type get_task_type() const { return m_taskType; }

    /**
     * @brief Get the usage details of the completion action.
     *
     * @return A string with the usage text of the completion action.
     */
    std::string usage() const override;

    /**
     * @brief Get a detailed description of the completion action.
     *
     * @return A string with the description of the completion action.
     */
    std::string description() const override;

  private:
    const task::Type m_taskType;

    /**
     * @brief Complete a todo task.
     */
    void run(const input::Input &input) override;
};

} // namespace action
} // namespace todo

#endif
