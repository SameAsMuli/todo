#include "action/reject.hpp"
#include "task/rejected.hpp"

namespace todo {
namespace action {

Reject::Reject(const input::Input &input)
    : AddCompleteAbstract("reject", "Mark a TODO as rejected", input,
                          new task::Rejected{}) {}

} // namespace action
} // namespace todo
