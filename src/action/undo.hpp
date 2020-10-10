#ifndef ACTION_UNDO_H
#define ACTION_UNDO_H

#include "action/action_abstract.hpp"
#include "util/input.hpp"

namespace todo {
namespace action {

/**
 * @brief Action to undo the completion of a task.
 */
class Undo : public ActionAbstract {

  public:
    /**
     * @brief Initialise the undo action.
     *
     * @param input The user's input.
     */
    Undo(util::Input input);

    /**
     * @brief Print the help text and list all available functions.
     */
    void run() override;
};

#endif

} // namespace action
} // namespace todo
