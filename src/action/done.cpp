#include "action/done.hpp"
#include "input/option.hpp"
#include "task/done.hpp"

namespace todo {
namespace action {

Done::Done(const input::Input &input)
    : AddAbstract("done", "Mark a TODO as finished", input, new task::Done{}) {
    this->addValidOption(input::Option::exact);
    this->addValidOption(input::Option::force);
}

} // namespace action
} // namespace todo
