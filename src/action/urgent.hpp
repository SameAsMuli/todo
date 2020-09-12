#ifndef ACTION_URGENT_H
#define ACTION_URGENT_H

#include "action/add_abstract.hpp"

namespace action {

class Urgent : public AddAbstract {

  public:
    Urgent(const util::Input &input);
};

} // namespace action

#endif
