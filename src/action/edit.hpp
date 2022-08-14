#ifndef ACTION_EDIT_H
#define ACTION_EDIT_H

#include "action/action_abstract.hpp"
#include "input/input.hpp"

namespace todo {
namespace action {

/**
 * @brief Action to edit a task.
 */
class Edit : public ActionAbstract {

  public:
    /**
     * @brief Initialise the edit action.
     */
    Edit();

    /**
     * @brief Get a detailed description of the edit action.
     *
     * @return A string with the description of the edit action.
     */
    std::string description() const override;

    /**
     * @brief Get the usage details of the edit action.
     *
     * @return A string with the usage text of the edit action.
     */
    std::string usage() const override;

  private:
    /**
     * @brief Edit a given task.
     */
    void run(const input::Input &input) override;
};

#endif

} // namespace action
} // namespace todo
