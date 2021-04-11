#include "action/add.hpp"
#include "input/option.hpp"
#include "task/normal.hpp"

namespace todo {
namespace action {

Add::Add(const input::Input &input)
    : AddAbstract("add", "Add a normal priority TODO", input,
                  new task::Normal{}) {
    this->addValidOption(input::Option::local);
}

} // namespace action
} // namespace todo
