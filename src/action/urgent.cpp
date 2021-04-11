#include "action/urgent.hpp"
#include "input/option.hpp"
#include "task/urgent.hpp"

namespace todo {
namespace action {

Urgent::Urgent(const input::Input &input)
    : AddAbstract("urgent", "Add an urgent priority TODO", input,
                  new task::Urgent{}) {
    this->addValidOption(input::Option::local);
}

} // namespace action
} // namespace todo
