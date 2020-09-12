#include "action/add.hpp"
#include "task/normal.hpp"

namespace action {

Add::Add(const util::Input &input)
    : AddAbstract("add", "Add a normal priority TODO", input,
                  new task::Normal{}) {}

} // namespace action
