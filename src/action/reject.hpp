#ifndef ACTION_REJECT_H
#define ACTION_REJECT_H

#include "action/add_abstract.hpp"

namespace action {

class Reject : public AddAbstract {

    public:
        Reject(const util::Input& input);
};

} // namespace action

#endif
