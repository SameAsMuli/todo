#include "action/reject.hpp"
#include "input/option.hpp"
#include "task/rejected.hpp"

namespace todo {
namespace action {

Reject::Reject(const input::Input &input)
    : AddAbstract("reject", "Mark a TODO as rejected", input,
                  new task::Rejected{}) {
    this->addValidOption(input::Option::exact);
    this->addValidOption(input::Option::force);
}

} // namespace action
} // namespace todo
