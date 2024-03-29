#ifndef ACTION_HIGH_H
#define ACTION_HIGH_H

#include "action/add_outstanding_abstract.hpp"

namespace todo {
namespace action {

/**
 * @brief Concrete variant of the add action for high priority tasks.
 */
class High : public AddOutstandingAbstract {

  public:
    /**
     * @brief Initialise the high action for high priority tasks.
     *
     * @param input The user's input.
     */
    High(const input::Input &input);
};

} // namespace action
} // namespace todo

#endif
