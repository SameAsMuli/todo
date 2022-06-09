#include "action/reject.hpp"
#include "task/rejected.hpp"

namespace todo {
namespace action {

Reject::Reject()
    : AddCompleteAbstract("reject", "Mark a TODO as rejected",
                          new task::Rejected{}) {}

} // namespace action
} // namespace todo
