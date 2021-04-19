#ifndef ACTION_ADD_ABSTRACT_H
#define ACTION_ADD_ABSTRACT_H

#include <string> // std::string

#include "action/action_abstract.hpp"
#include "input/input.hpp"
#include "task/task_type_abstract.hpp"

namespace todo {
namespace action {

/**
 * @brief Abstract class to govern the interface for adding tasks.
 */
class AddAbstract : public ActionAbstract {

  public:
    /**
     * @brief Base constructor for an add action.
     *
     * @param name The name of the action.
     * @param helpText A short description of the action.
     * @param input The user's input to be passed to the action.
     * @param taskType The type of task this class will add.
     */
    AddAbstract(const std::string &name, const std::string &helpText,
                const input::Input &input,
                task::TaskTypeAbstract *const taskType);

    /**
     * @brief Get the type of task added by this action.
     *
     * @return The task type for this action.
     */
    task::TaskTypeAbstract *getTaskType() const { return m_taskType; }

    /**
     * @brief Get the usage details of the add action.
     *
     * @return A string with the usage text of the add action.
     */
    std::string usage() const override;

  private:
    task::TaskTypeAbstract *const m_taskType;

    /**
     * @brief Add a todo task.
     */
    void run() override;
};

} // namespace action
} // namespace todo

#endif
