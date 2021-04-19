#ifndef ACTION_REJECT_H
#define ACTION_REJECT_H

#include "action/add_complete_abstract.hpp"
#include "input/input.hpp"

namespace todo {
namespace action {

/**
 * @brief Concrete variant of the add action for rejected tasks.
 */
class Reject : public AddCompleteAbstract {

  public:
    /**
     * @brief Initialise the reject action.
     *
     * @param input The user's input.
     */
    Reject(const input::Input &input);
};

} // namespace action
} // namespace todo

#endif
