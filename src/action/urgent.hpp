#include "action/add_abstract.hpp"

#ifndef ACTION_URGENT_H
#define ACTION_URGENT_H

namespace action {

class Urgent : public AddAbstract {

    public:
        Urgent(const util::Input& input);
};

} // namespace action

#endif
