#ifndef ACTION_ADD_H
#define ACTION_ADD_H

#include "action/add_abstract.hpp"

namespace action {

/**
 * @brief Concrete variant of the add action for normal priority tasks.
 */
class Add : public AddAbstract {

  public:
    /**
     * @brief Initialise the add action for normal priority tasks.
     *
     * @param input The user's input.
     */
    Add(const util::Input &input);
};

} // namespace action

#endif
