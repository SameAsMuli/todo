#ifndef ACTION_ADD_COMPLETE_ABSTRACT_H
#define ACTION_ADD_COMPLETE_ABSTRACT_H

#include <string> // std::string

#include "action/add_abstract.hpp"
#include "input/input.hpp"
#include "task/task_type_abstract.hpp"

namespace todo {
namespace action {

/**
 * @brief Variant of the add action for complete tasks.
 */
class AddCompleteAbstract : public AddAbstract {

  public:
    /**
     * @brief Base constructor for an add action for complete tasks.
     *
     * @param name The name of the action.
     * @param helpText A short description of the action.
     * @param input The user's input to be passed to the action.
     * @param taskType The type of task this class will add.
     */
    AddCompleteAbstract(const std::string &name, const std::string &helpText,
                        const input::Input &input,
                        task::TaskTypeAbstract *const taskType);

    /**
     * @brief Get a detailed description of the add complete action.
     *
     * @return A string with the description of the add complete action.
     */
    std::string description() const override;
};

} // namespace action
} // namespace todo

#endif
