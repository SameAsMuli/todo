#include "action/low.hpp"
#include "input/option.hpp"
#include "task/low.hpp"

namespace todo {
namespace action {

Low::Low(const input::Input &input)
    : AddAbstract("low", "Add a low priority TODO", input,
                  {input::Option::local}, new task::Low{}) {}

} // namespace action
} // namespace todo
