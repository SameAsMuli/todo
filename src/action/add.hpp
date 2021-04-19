#ifndef ACTION_ADD_H
#define ACTION_ADD_H

#include "action/add_outstanding_abstract.hpp"

namespace todo {
namespace action {

/**
 * @brief Concrete variant of the add action for normal priority tasks.
 */
class Add : public AddOutstandingAbstract {

  public:
    /**
     * @brief Initialise the add action for normal priority tasks.
     *
     * @param input The user's input.
     */
    Add(const input::Input &input);
};

} // namespace action
} // namespace todo

#endif
