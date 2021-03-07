#ifndef ACTION_REMOVE_H
#define ACTION_REMOVE_H

#include "action/action_abstract.hpp"
#include "input/input.hpp"

namespace todo {
namespace action {

/**
 * @brief Action to remove a task.
 */
class Remove : public ActionAbstract {

  public:
    /**
     * @brief Initialise the remove action.
     *
     * @param input The user's input.
     */
    Remove(input::Input input);

    /**
     * @brief Remove matching task.
     */
    void run() override;
};

#endif

} // namespace action
} // namespace todo
