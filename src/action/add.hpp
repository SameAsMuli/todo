#ifndef ACTION_ADD_H
#define ACTION_ADD_H

#include "action/add_abstract.hpp"

namespace action {

class Add : public AddAbstract {

  public:
    Add(const util::Input &input);
};

} // namespace action

#endif
