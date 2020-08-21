#include "action/add_abstract.hpp"

#ifndef URGENT_ACTION_H
#define URGENT_ACTION_H

namespace action {

class Urgent : public AddAbstract {

    public:
        Urgent(const util::Input& input,
                const std::filesystem::path& file);
};

} // namespace action

#endif
