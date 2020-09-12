#ifndef ACTION_LOW_H
#define ACTION_LOW_H

#include "action/add_abstract.hpp"

namespace action {

class Low : public AddAbstract {

  public:
    Low(const util::Input &input);
};

} // namespace action

#endif
