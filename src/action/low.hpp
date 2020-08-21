#include "action/add_abstract.hpp"

#ifndef LOW_ACTION_H
#define LOW_ACTION_H

namespace action {

class Low : public AddAbstract {

    public:
        Low(const util::Input& input, const std::filesystem::path& file);
};

} // namespace action

#endif
