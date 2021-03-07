#ifndef ACTION_DONE_H
#define ACTION_DONE_H

#include "action/add_abstract.hpp"

namespace todo {
namespace action {

/**
 * @brief Concrete variant of the add action for done tasks.
 */
class Done : public AddAbstract {

  public:
    /**
     * @brief Initialise the done action for tasks.
     *
     * @param input The user's input.
     */
    Done(const input::Input &input);
};

} // namespace action
} // namespace todo

#endif
