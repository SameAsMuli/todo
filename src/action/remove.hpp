#ifndef ACTION_REMOVE_H
#define ACTION_REMOVE_H

#include "action/action_abstract.hpp"
#include "util/input.hpp"

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
    Remove(util::Input input);

    /**
     * @brief Print the help text and list all available functions.
     */
    void run() override;
};

#endif

} // namespace action
