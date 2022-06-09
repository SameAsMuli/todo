#ifndef ACTION_UNDO_H
#define ACTION_UNDO_H

#include "action/action_abstract.hpp"
#include "input/input.hpp"

namespace todo {
namespace action {

/**
 * @brief Action to undo the completion of a task.
 */
class Undo : public ActionAbstract {

  public:
    /**
     * @brief Initialise the undo action.
     */
    Undo();

    /**
     * @brief Get a detailed description of the undo action.
     *
     * @return A string with the description of the undo action.
     */
    std::string description() const override;

    /**
     * @brief Print the help text and list all available functions.
     */
    void run(const input::Input &input) override;
};

#endif

} // namespace action
} // namespace todo
