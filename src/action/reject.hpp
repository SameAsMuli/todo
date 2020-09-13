#ifndef ACTION_REJECT_H
#define ACTION_REJECT_H

#include "action/add_abstract.hpp"

namespace action {

/**
 * @brief Concrete variant of the add action for rejected tasks.
 */
class Reject : public AddAbstract {

  public:
    /**
     * @brief Initialise the reject action tasks.
     *
     * @param input The user's input.
     */
    Reject(const util::Input &input);
};

} // namespace action

#endif
