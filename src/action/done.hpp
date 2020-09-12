#ifndef ACTION_DONE_H
#define ACTION_DONE_H

#include "action/add_abstract.hpp"

namespace action {

class Done : public AddAbstract {

    public:
        Done(const util::Input& input);
};

} // namespace action

#endif
