#include "action/add.hpp"
#include "task/normal.hpp"

namespace todo {
namespace action {

Add::Add(const input::Input &input)
    : AddAbstract("add", "Add a normal priority TODO", input,
                  new task::Normal{}) {}

} // namespace action
} // namespace todo
