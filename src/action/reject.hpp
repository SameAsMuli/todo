#include "action/add_abstract.hpp"

#ifndef ACTION_REJECT_H
#define ACTION_REJECT_H

namespace action {

class Reject : public AddAbstract {

    public:
        Reject(const util::Input& input);
};

} // namespace action

#endif
