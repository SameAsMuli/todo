#ifndef ACTION_LOW_H
#define ACTION_LOW_H

#include "action/add_outstanding_abstract.hpp"

namespace todo {
namespace action {

/**
 * @brief Concrete variant of the add action for low priority tasks.
 */
class Low : public AddOutstandingAbstract {

  public:
    /**
     * @brief Initialise the low action for low priority tasks.
     */
    Low();
};

} // namespace action
} // namespace todo

#endif
