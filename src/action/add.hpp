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
     */
    Add();
};

} // namespace action
} // namespace todo

#endif
