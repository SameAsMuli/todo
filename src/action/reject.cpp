#include "action/reject.hpp"
#include "task/rejected.hpp"

namespace action {

Reject::Reject(const util::Input& input):
    AddAbstract( "reject", "Mark a TODO as rejected", input,
            new task::Rejected{})
{ }

} // namespace action
