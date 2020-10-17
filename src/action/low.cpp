#include "action/low.hpp"
#include "task/low.hpp"

namespace todo {
namespace action {

Low::Low(const util::Input &input)
    : AddAbstract("low", "Add a low priority TODO", input, new task::Low{}) {}

} // namespace action
} // namespace todo
