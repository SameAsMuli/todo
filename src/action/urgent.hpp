#ifndef ACTION_URGENT_H
#define ACTION_URGENT_H

#include "action/add_outstanding_abstract.hpp"

namespace todo {
namespace action {

/**
 * @brief Concrete variant of the add action for urgent priority tasks.
 */
class Urgent : public AddOutstandingAbstract {

  public:
    /**
     * @brief Initialise the urgent action for high priority tasks.
     *
     * @param input The user's input.
     */
    Urgent(const input::Input &input);
};

} // namespace action
} // namespace todo

#endif
