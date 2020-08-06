#include "action/add_abstract.hpp"

#ifndef ADD_ACTION_H
#define ADD_ACTION_H

namespace action {

class Add : public AddAbstract {

    public:
        Add(const util::InputParser& input, const std::filesystem::path& file);
};

} // namespace action

#endif
