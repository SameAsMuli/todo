#ifndef ACTION_ADD_ABSTRACT_H
#define ACTION_ADD_ABSTRACT_H

#include <filesystem> // std::filesystem

#include "action/action_abstract.hpp"
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
     * @param validOptions The list of options accepted by this action.
     * @param taskType The type of task this class will add.
     */
    AddAbstract(const std::string &name, const std::string &helpText,
                const input::Input &input,
                const std::unordered_set<input::Option> &validOptions,
                task::TaskTypeAbstract *const taskType);

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
