#ifndef ACTION_LOW_H
#define ACTION_LOW_H

#include "action/add_abstract.hpp"

namespace action {

/**
 * @brief Concrete variant of the add action for low priority tasks.
 */
class Low : public AddAbstract {

  public:
    /**
     * @brief Initialise the low action for low priority tasks.
     *
     * @param input The user's input.
     */
    Low(const util::Input &input);
};

} // namespace action

#endif
